[BITS 16]
; 常量
KERNEL_OFFSET equ 0x1000	; 内核加载到0x1000的内存地址
; 加载内核kernel.bin到KERNEL_OFFSET地址上
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print_string

	mov bx, KERNEL_OFFSET
	mov dh, 0x30	;  需要注意读取的扇区数！过小导致加载不完全。
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

MSG_LOAD_KERNEL: db 'Loading NetcanOS kernel into memory', 0xa, 0xd, 0
