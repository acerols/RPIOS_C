CROSS = aarch64-linux-gnu
CC = ${CROSS}-gcc
AS = ${CROSS}-as
OBJDUMP = ${CROSS}-objdump
CFLAGS =  -mcpu=cortex-a53 -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra -Iinclude/
ASM_FLAGS = -mcpu=cortex-a53 -Iinclude/
SRCS = $(wildcard *.c)
SRCSA = $(wildcard *.S)
OBJ = $(SRCS:.c=.o)
OBJ += $(SRCSA:.S=.o) 

kernel.elf: ${OBJ}
	${CC} -Wl,--build-id=none -T link.ld -o $@ -ffreestanding -O2 -nostdlib ${OBJ}
	${OBJDUMP} -D kernel.elf > kernel.list

%.o: %.S
	${AS} ${ASM_FLAGS} -c $< -o $@

%.o : %.c Makefile
	$(CC) ${CFLAGS} -c -o $*.o $*.c

run :
	$(MAKE) kernel.elf
	qemu-system-aarch64 -M raspi3 -m 128 -serial mon:stdio -nographic -kernel kernel.elf

runasm :
	$(MAKE) kernel.elf
	qemu-system-aarch64 -M raspi3 -m 128 -serial mon:stdio -nographic -kernel kernel.elf -d in_asm

clean:
	rm -f *.o *.elf *.list

.PHONY: clean
