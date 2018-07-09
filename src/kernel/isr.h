/*************************************************************************
	> File Name: kernel/isr.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-09 Mon 22:47:21 CST
 ************************************************************************/

#include <io.h>
#ifndef ISR_H
#define ISR_H
typedef struct registers {
	u32 ds;                  // 数据段选择
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // 通用寄存器
	u32 int_no, err_code;    // 中断号、错误码
	u32 eip, cs, eflags, sp, ss; // 中断恢复
} registers_t;

void isr_handler(registers_t regs);

#endif
