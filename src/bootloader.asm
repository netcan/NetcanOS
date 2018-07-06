
BITS 16
[org 0x7c00]

main:
	mov dx, 0x2333
	call print_hex
	mov bx, hello
	call print_string
	jmp $

%include "util/print.asm"

hello: db "Hello World! From Netcan OS", 0
times 510 - ($-$$) db 0
dw 0xaa55
