/*************************************************************************
	> File Name: cpu/timer.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-11 Wed 22:04:23 CST
 ************************************************************************/

#include <timer.h>
#include <int_handler.h>
#include <stdio.h>

u32 tick = 0; //!< 定时器中断次数

static void timer_callback(registers_t regs) {
	/*printf("tick: %d\n", tick);*/
	++tick;
}

/* 初始化定时器。
 * @param freq 定时器频率
 */
void init_timer(u32 freq) {
	register_int_handler(IRQ0, &timer_callback);
	u16 divisor = MAX_FREQ / freq;
	port_byte_out(TIMER_CONTROL, 0x36);	// 0x36为重复模式，反复发送中断

	// 设置分频
	port_byte_out(TIMER_CHANNEL_DATA_0, divisor & 0xff);
	port_byte_out(TIMER_CHANNEL_DATA_0, (divisor >> 8) & 0xff);
}
