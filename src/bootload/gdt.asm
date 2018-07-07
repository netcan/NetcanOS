; 定义一个GDT表，含3个实体（每个8字节），分别为NULL段，代码段，数据段。
gdt_start:

gdt_null:   ; 8字节的NULL段
    dd 0x0
    dd 0x0

gdt_code:   ; 定义代码段
; base=0x0, limit=0xfffff,
; 1st flags: (present)1 (privilege)00 (descriptor type)1 -> 1001b
; type flags: (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010b
; 2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 1100b
    dw 0xffff   ; segment limit(0:15)
    dw 0x0      ; base address(0:15)
    db 0x0      ; base address(16:23)
    db 10011010b; 1st flags和type flags
    db 11001111b; 2nd flags和segment limit(16:19)
    db 0x0      ; base address(24:31)

gdt_data:   ; 定义数据段
; 和代码段一样，除了type字段：
; type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
    dw 0xffff   ; segment limit(0:15)
    dw 0x0      ; base address(0:15)
    db 0x0      ; base address(16:23)
    db 10010010b; 1st flags和type flags
    db 11001111b; 2nd flags和segment limit(16:19)
    db 0x0      ; base address(24:31)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; gdt的大小
    dd gdt_start                ; gdt的地址

CODE_SEG equ gdt_code - gdt_start   ; 段寄存器的索引，gdt[DS]
DATA_SEG equ gdt_data - gdt_start
