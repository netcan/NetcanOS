/*************************************************************************
	> File Name: cpu/timer.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-11 Wed 22:04:30 CST
 ************************************************************************/

/** 定时器，产生定时中断。
 * 频率范围：18.2 Hz ~ 1193180 Hz
 */
#include <io.h>
#ifndef TIMER_H
#define TIMER_H
#define TIMER_CHANNEL_DATA_0 0x40 //!< 定时器信道数据端口0，连接中断IRQ0
#define TIMER_CHANNEL_DATA_1 0x41 //!< 定时器信道数据端口1，已废弃，用于控制DRAM的刷新率
#define TIMER_CHANNEL_DATA_2 0x42 //!< 定时器信道数据端口2，用于控制扬声器频率
#define TIMER_CONTROL	0x43	//!< 定时器控制端口
#define MAX_FREQ 1193180	//!< 定时器最大值

extern u32 tick;
void init_timer(u32 freq);

#endif
