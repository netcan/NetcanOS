[BITS 16]
; 切换到32位保护模式
switch_to_pm:
    cli                     ; 关中断，直到设置保护模式的中断向量表
    lgdt [gdt_descriptor]   ; 告诉CPU gdt表的位置
    mov eax, cr0            ; 设置cr0寄存器的第0位
    or eax, 0x01
    mov cr0, eax

    jmp CODE_SEG:init_pm    ; far jump，会自动将cs更新为目标段。

[BITS 32]
; 保护模式初始化，重置段寄存器
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; 栈指针
    mov esp, ebp

    call begin_pm   ; 进入保护模式程序

; 开始执行保护模式下的程序
begin_pm:
	mov ebx, PROT_HELLO
	call print_string_pm

	call KERNEL_OFFSET	; jmp, 执行内核代码
	jmp $
