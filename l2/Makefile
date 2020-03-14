TOOLCHAIN = aarch64-linux-gnu

CC = $(TOOLCHAIN)-gcc
ASM = $(TOOLCHAIN)-gcc
LD = $(TOOLCHAIN)-ld

CFLAGS = -Wall -nostdlib -ffreestanding -Iinclude -mgeneral-regs-only
ASFLAGS = -Iinclude

BUILD_DIR = build
SRC_DIR = src

all : kernel8.img

clean :
	rm -rf $(BUILD_DIR) *.img

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.s
	$(ASM) $(ASFLAGS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.s)
OBJ = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ += $(ASM_FILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ)
	$(LD) -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ)
	$(TOOLCHAIN)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img

run:
	/mnt/c/Users/acero/qemu/build/bin/qemu-system-aarch64 \
	-m 128 -M raspi3 -nographic -kernel src/kernel8.elf