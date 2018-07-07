[BITS 16]
; 打印16进制数，使用dx传参
print_hex:
	pusha
	mov cx, 4			; 清零
	mov al, [hex_digit] ; '0'
	.clear:
		mov bx, cx
		mov [hex_out + 1 + bx], al
		loop .clear

	mov cx, 4
	.repeat:
		mov bx, dx
		and bx, 0x0f ; 取出最后一位
		mov al, [bx + hex_digit]
		mov bx, cx
		mov [hex_out + 1 + bx], al
		shr dx, 0x4
		loop .repeat


	mov bx, hex_out
	call print_string

	.done:
		popa
		ret

; 打印字符串，使用bx传参，bx为字符串地址
print_string:
	pusha
	mov ah, 0xe
	.repeat:
		mov al, [bx]
		cmp al, 0
		je .done
		int 0x10
		inc bx
		jmp .repeat
	.done:
		popa
		ret

; 全局变量区
hex_out: db '0x0000', 0x0a, 0xd, 0 ; 模板串，CRLF
hex_digit: db '0123456789abcdef'
