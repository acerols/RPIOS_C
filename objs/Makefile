include ../Makefile

img:
	ld.lld -m aarch64elf -nostdlib $(OBJS) -T link.ld -o kernel8.elf
	$(OBJCOPY) -O binary kernel8.elf kernel8.img