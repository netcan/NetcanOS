[BITS 32]

%macro ISR_NO_ERRORCODE 1	; 中断处理程序无错误版本
	[GLOBAL isr%1]
	isr%1:
		cli			; 关中断
		push byte 0	; 占位符，保证栈结构的一致性
		push byte %1	; 中断号
		jmp isr_common_stub	; 中断通用处理程序
%endmacro

%macro ISR_ERRORCODE 1	; 中断处理程序有错误号版本
	[GLOBAL isr%1]
	isr%1:
		cli			; 关中断
		push byte %1	; 中断号
		jmp isr_common_stub	; 中断通用处理程序
%endmacro


ISR_NO_ERRORCODE 0
ISR_NO_ERRORCODE 1
ISR_NO_ERRORCODE 2
ISR_NO_ERRORCODE 3
ISR_NO_ERRORCODE 4
ISR_NO_ERRORCODE 5
ISR_NO_ERRORCODE 6
ISR_NO_ERRORCODE 7
ISR_ERRORCODE 8
ISR_NO_ERRORCODE 9
ISR_ERRORCODE 10
ISR_ERRORCODE 11
ISR_ERRORCODE 12
ISR_ERRORCODE 13
ISR_ERRORCODE 14
ISR_NO_ERRORCODE 15
ISR_NO_ERRORCODE 16
ISR_NO_ERRORCODE 17
ISR_NO_ERRORCODE 18
ISR_NO_ERRORCODE 19
ISR_NO_ERRORCODE 20
ISR_NO_ERRORCODE 21
ISR_NO_ERRORCODE 22
ISR_NO_ERRORCODE 23
ISR_NO_ERRORCODE 24
ISR_NO_ERRORCODE 25
ISR_NO_ERRORCODE 26
ISR_NO_ERRORCODE 27
ISR_NO_ERRORCODE 28
ISR_NO_ERRORCODE 29
ISR_NO_ERRORCODE 30
ISR_NO_ERRORCODE 31

; C语言版本的通用中断处理程序
[EXTERN isr_handler]
isr_common_stub:
	pusha	; 保存通用寄存器
	mov eax, ds
	push eax

    mov ax, 0x10	; 数据段
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	call isr_handler	; 中断处理程序

	pop eax			; 还原ds
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	popa		; 还原通用寄存器
	add esp, 8	; 清理错误码、中断号
	sti			; 开中断
	iret		; 恢复 cs, ip, flags, ss, sp




