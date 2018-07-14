/*************************************************************************
	> File Name: kernel/init_handler.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-09 Mon 22:47:21 CST
 ************************************************************************/

#include <io.h>
#ifndef INIT_HANDLER_H
#define INIT_HANDLER_H
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct registers {
	u32 ds;                  // 数据段选择
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // 通用寄存器
	u32 int_no, err_code;    // 中断号、错误码
	u32 eip, cs, eflags, sp, ss; // 中断恢复
} registers_t;

void isr_handler(registers_t regs);

typedef void (*int_handler_t)(registers_t);
extern int_handler_t int_handlers[0x100];
void register_int_handler(u8 int_no, int_handler_t handler);
#endif
