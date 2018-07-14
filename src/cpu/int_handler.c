/*************************************************************************
	> File Name: kernel/int_handler.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-09 Mon 22:47:04 CST
 ************************************************************************/

#include <int_handler.h>
#include <descriptor_tables.h>
#include <stdio.h>

int_handler_t int_handlers[0x100];   // 中断处理程序，函数指针数组
/** 注册中断程序
 * @params int_no 中断号
 * @params handler 中断处理程序
 */
void register_int_handler(u8 int_no, int_handler_t handler) {
    int_handlers[int_no] = handler;
}


/** 中断处理程序（中断号<32，又叫异常），处理系统中断system error。
 * @param regs 寄存器信息
 */
void isr_handler(registers_t regs) {
	printf("ISR(Exception) recieved: 0x%02x\n", regs.int_no);
    if(int_handlers[regs.int_no]) int_handlers[regs.int_no](regs);
}

/** 中断处理程序（中断号32-47）
 * @param regs 寄存器信息
 */
void irq_handler(registers_t regs) {
    /*printf("IRQ recieved: 0x%02x\n", regs.int_no);*/
    if(int_handlers[regs.int_no]) int_handlers[regs.int_no](regs);

    if(regs.int_no >= 40)  // 通知slave pic和master pic，发送EOI信息。
        port_byte_out(PIC_SLAVE_CONTROL, PIC_EOI);
    port_byte_out(PIC_MASTER_CONTROL, PIC_EOI);
}
