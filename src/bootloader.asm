[BITS 16]
[ORG 0x7c00]

main:
	mov [BOOT_DRIVE], dl	; BIOS将启动磁盘号记录在dl
	mov bp, 0x8000			; 设置栈底指针
	mov sp, bp

	mov dx, 0x2333
	call print_hex		; 打印0x2333
	mov bx, REAL_HELLO
	call print_string	; 打印HELLO
	; 磁盘检测
	mov bx, 0x9000
	mov dh, 2			; 读取2块扇区到[0x0000:0x9000]中
	mov dl, [BOOT_DRIVE]
	call disk_load
	mov dx, [0x9000]		; 打印0x9000的内存数据
	call print_hex
	mov dx, [0x9000 + 512]	; 打印第二块扇区的内容
	call print_hex

	call switch_to_pm		; 切换到保护模式
	jmp $


%include "util/print.asm"
%include "util/print_pm.asm"
%include "util/disk_load.asm"
%include "gdt.asm"
%include "switch_to_pm.asm"

[BITS 32]
BEGIN_PM:
	mov ebx, PROT_HELLO
	call print_string_pm
	jmp $

; 全局变量
REAL_HELLO: db "Hello World! From Netcan OS, Started in 16 bit Real Mode", 0xa, 0xd, 0
PROT_HELLO: db "Hello World! From Netcan OS, Successfully landed in 32 bit Protected Mode", 0
BOOT_DRIVE: db 0

; 填充并设置为启动扇区
times 510 - ($-$$) db 0
dw 0xaa55

times 256 dw 0xabab		; 填充剩下的两块扇区
times 256 dw 0xbaba
