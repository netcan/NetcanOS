; 32位保护模式下的print_string函数，ebx存放字符串地址
[BITS 32]
; 常量区
VRAM_ADDR equ 0xb8000   ; 显存地址
WHITE_ON_BLACK equ 0x0f ; 黑底白字

print_string_pm:
    pusha
    mov edx, VRAM_ADDR
    .loop:
        mov al, [ebx]
        mov ah, WHITE_ON_BLACK

        cmp al, 0
        je .done
        mov [edx], ax   ; 写数据到显存中
        inc ebx         ; 移动到下一个字符
        add edx, 2      ; 移动到下一格
        jmp .loop

    .done:
        popa
        ret
