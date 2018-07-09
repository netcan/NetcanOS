add-symbol-file kernel/kernel.elf 0x1000
target remote | qemu-system-i386 -S -gdb stdio -fda NetcanOS.bin
