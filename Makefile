#
# Copyright (C) 2018 bzt (bztsrc@github)
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#

SRCS = $(wildcard *.c)
SRCSA = $(wildcard *.S)
OBJS = $(SRCS:.c=.o)
OBJS += $(SRCSA:.S=.o) 
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a53+nosimd -I./include
OBJCOPY = llvm-objcopy
OBJSDIR = ./objs/
all: clean kernel8.img

%.o: %.S
	clang --target=aarch64-elf $(CFLAGS) -c $< -o $(OBJSDIR)$@

%.o: %.c
	clang --target=aarch64-elf $(CFLAGS) -c $< -o $(OBJSDIR)$@

kernel8.img: $(OBJS)
	ld.lld -m aarch64elf -nostdlib $(OBJSDIR)*.o -T link.ld -o kernel8.elf
	$(OBJCOPY) -O binary kernel8.elf kernel8.img

win:
	@make OBJCOPY=llvm-objcopy-10

clean:
	rm kernel8.elf *.o >/dev/null 2>/dev/null || true

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio

runout:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial pty

runasm:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio -d in_asm
