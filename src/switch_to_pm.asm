[BITS 16]
; 切换到32位保护模式
switch_to_pm:
    cli ; 关中断，直到设置保护模式的中断向量表
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x01
    mov cr0, eax

    jmp CODE_SEG:init_pm

[BITS 32]
; 保护模式初始化，重置段寄存器
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ;
    mov esp, ebp

    call BEGIN_PM   ; 进入保护模式程序
