/*************************************************************************
	> File Name: kernel/io.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 13:17:16 CST
 ************************************************************************/
#ifndef IO_H
#define IO_H
// in 指令，从IO端口读取数据
unsigned char port_byte_in(unsigned short port);
unsigned short port_word_in(unsigned short port);

// out 指令，往IO端口输出数据
void port_byte_out(unsigned short port, unsigned char data);
void port_word_out(unsigned short port, unsigned short data);
#endif
