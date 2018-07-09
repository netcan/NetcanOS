CC = i386-elf-gcc
LD = i386-elf-ld
GDB = i386-elf-gdb
OBJCOPY = i386-elf-objcopy
NASM = nasm
CFLAGS = -g -m32 -ffreestanding -c -Ikernel -Idrivers -Ilibc

C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c) # wildchard展开通配符列表
HEADERS = $(wildcard kernel/*.h drivers/*.h libc/*.h)
OBJS = $(C_SOURCES:.c=.o) # 将.c替换为.o


all: NetcanOS.img

NetcanOS.img: boot/bootloader.bin kernel/kernel.bin
	cat $^ > $@

kernel/kernel.bin: kernel/kernel.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

%.o: %.asm
	$(NASM) $< -f elf -I boot/ -o $@

%.bin: %.asm
	$(NASM) $< -f bin -I boot/ -o $@

# 调试用
kernel/kernel.elf: kernel/kernel_entry.o $(OBJS)
	$(LD) -o $@ -Ttext 0x1000 $^

run: NetcanOS.img
	#bochs
	qemu-system-i386 -fda NetcanOS.img

debug: NetcanOS.img kernel/kernel.elf kernel.gdb
	$(GDB) -x kernel.gdb

clean:
	rm -rf NetcanOS.img
	rm -rf kernel/*.bin kernel/*.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o libc/*.o
