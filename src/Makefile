CC = i386-elf-gcc-8.1.0
LD = i386-elf-ld
GDB = i386-elf-gdb
NASM = nasm
CFLAGS = -g -m32 -ffreestanding -c -Ikernel -Idrivers -Ilibc

C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c) # wildchard展开通配符列表
HEADERS = $(wildcard kernel/*.h drivers/*.h libc/*.h)
OBJS = $(C_SOURCES:.c=.o) # 将.c替换为.o


all: NetcanOS.img

NetcanOS.img: boot/bootloader.bin kernel/kernel.bin
	cat $^ > $@

kernel/kernel.bin: kernel/kernel_entry.o $(OBJS)
	$(LD) -Ttext 0x1000 --oformat binary $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

%.o: %.asm
	$(NASM) $< -f elf -I boot/ -o $@

%.bin: %.asm
	$(NASM) $< -f bin -I boot/ -o $@

# 调试用
kernel.elf: kernel/kernel_entry.o ${OBJS}
	$(LD) -o $@ -Ttext 0x1000 $^

run: NetcanOS.img
	#bochs
	qemu-system-i386 -fda NetcanOS.img

debug: NetcanOS.img kernel.elf kernel.gdb
	$(GDB) -x kernel.gdb

clean:
	rm -rf NetcanOS.img
	rm -rf kernel/*.bin
	rm -rf kernel/*.o boot/*.bin
