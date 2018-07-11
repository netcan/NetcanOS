[BITS 32]

; 告诉CPU GDT表位置
[GLOBAL gdt_flush]	; 让C语言能够调用
gdt_flush:
	mov eax, [esp + 4]
	lgdt [eax]		; gdt_ptr
    mov ax, 0x10	; 设置数据段
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	jmp 0x8:.flush	; 设置代码段cs

	.flush:
		ret

; 告诉CPU IDT表位置
[GLOBAL idt_flush]	; 让C语言能够调用
idt_flush:
	mov eax, [esp + 4]	; idt_ptr
	lidt [eax]
	sti	; 开中断，之前忘了导致定时器无法工作。
	ret

