[BITS 16]
; 读取磁盘数据到[ES:BX]，dl指定第几个磁盘，dh指定读取几块扇区
disk_load:
    push dx
    mov ah, 0x02    ; 设置BIOS读取扇区程序参数
    mov al, dh      ; 设置读取的扇区数量
    mov ch, 0x00    ; 设置读取第0个柱面
    mov cl, 0x02    ; 设置读取第2个扇区
    mov dh, 0x00    ; 设置第0个磁头

    int 0x13        ; BIOS读取扇区中断程序
    pop dx

    jc disk_error   ; 读取失败会设置CF位
	cmp al, dh      ; al记录了成功读取扇区块数
	jne disk_error
    ret


disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $


; 全局变量区
DISK_ERROR_MSG: db "DISK read error!", 0xa, 0xd, 0

