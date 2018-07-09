/*************************************************************************
	> File Name: kernel/isr.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-09 Mon 22:47:04 CST
 ************************************************************************/

#include <isr.h>
#include <stdio.h>

/** 中断处理程序
 * @param regs 寄存器信息
 */
void isr_handler(registers_t regs) {
	printf("ISR recieved: 0x%02x\n", regs.int_no);
}
