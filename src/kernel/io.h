/*************************************************************************
	> File Name: kernel/io.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 13:17:16 CST
 ************************************************************************/
#include <stddef.h>
#include <stdio.h>

#ifndef IO_H
#define IO_H
#define ASSERT(cond, msg) if(!(cond)) { printf("%s at %s:%d\n", msg, __FILE__, __LINE__); while(1); }
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned char u8;
typedef signed char s8;

// in 指令，从IO端口读取数据
u8 port_byte_in(u16 port);
u16 port_word_in(u16 port);

// out 指令，往IO端口输出数据
void port_byte_out(u16 port, u8 data);
void port_word_out(u16 port, u16 data);
#endif
