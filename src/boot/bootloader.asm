[BITS 16]
[ORG 0x7c00]

main:
	mov [BOOT_DRIVE], dl	; BIOS将启动磁盘号记录在dl
	mov bp, 0x9000			; 设置栈底指针
	mov sp, bp

	mov dx, 0x2333
	call print_hex		; 打印0x2333
	mov bx, REAL_HELLO
	call print_string	; 打印HELLO

	call load_kernel

	call switch_to_pm		; 切换到32位保护模式
	jmp $


%include "util/print.asm"
%include "util/print_pm.asm"
%include "util/disk_load.asm"
%include "load_kernel.asm"
%include "gdt.asm"
%include "switch_to_pm.asm"

; 全局变量
REAL_HELLO: db "Hello World! From Netcan OS, Started in 16 bit Real Mode", 0xa, 0xd, 0
PROT_HELLO: db "Hello World! From Netcan OS, Successfully landed in 32 bit Protected Mode", 0
BOOT_DRIVE: db 0

; 填充并设置为启动扇区
times 510 - ($-$$) db 0
dw 0xaa55
