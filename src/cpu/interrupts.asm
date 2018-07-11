[BITS 32]

%macro ISR_NO_ERRORCODE 1	; 中断处理程序无错误版本(system error, 中断号<32)
	[GLOBAL isr%1]
	isr%1:
		cli			; 关中断
		push byte 0	; 占位符，保证栈结构的一致性
		push byte %1	; 中断号
		jmp isr_common_stub	; 中断通用处理程序
%endmacro

%macro ISR_ERRORCODE 1	; 中断处理程序有错误号版本(system error, 中断号<32)
	[GLOBAL isr%1]
	isr%1:
		cli			; 关中断
		push byte %1	; 中断号
		jmp isr_common_stub	; 中断通用处理程序
%endmacro

%macro IRQ 2	; 中断号>=32，两个宏参数
	[GLOBAL irq%1]
	irq%1:
		cli			; 关中断
		push byte 0
		push byte %2	; 中断号
		jmp irq_common_stub	; 中断通用处理程序
%endmacro


; CPU定义的32个system error中断程序
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

; 32-47号中断
IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47


; C语言版本的通用中断处理程序
%macro COMMON_STUB 1
[EXTERN %1_handler]
%1_common_stub:
	pusha	; 保存通用寄存器
	mov eax, ds
	push eax

	mov ax, 0x10	; 数据段
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call %1_handler	; 中断处理程序

	pop eax			; 还原ds
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popa		; 还原通用寄存器
	add esp, 8	; 清理错误码、中断号
	sti			; 开中断
	iret		; 恢复 cs, ip, flags, ss, sp
%endmacro

COMMON_STUB isr
COMMON_STUB irq
