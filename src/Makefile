CC=i386-elf-gcc-8.1.0
LD=i386-elf-ld
NASM=nasm

# wildchard展开通配符列表
C_SOURCES=$(wildcard kernel/*.c)
HEADERS=$(wildcard kernel/*.h)
# 将.c替换为.o
OBJS = $(C_SOURCES:.c=.o)

all: NetcanOS.img

NetcanOS.img: boot/bootloader.bin kernel/kernel.bin
	cat $^ > $@

kernel/kernel.bin: kernel/kernel_entry.o $(OBJS)
	$(LD) -Ttext 0x1000 --oformat binary $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) -m32 -ffreestanding -c $< -o $@

%.o: %.asm
	$(NASM) $< -f elf -I boot/ -o $@

%.bin: %.asm
	$(NASM) $< -f bin -I boot/ -o $@

run:
	bochs

clean:
	rm -rf NetcanOS.img
	rm -rf kernel/*.bin
	rm -rf kernel/*.o boot/*.bin
