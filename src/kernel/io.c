/*************************************************************************
	> File Name: kernel/io.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 11:26:07 CST
 ************************************************************************/
#include <io.h>

/** 从IO端口读取8位数据。
 * @param port 端口
 * @return 读取的数据。
 */
u8 port_byte_in(u16 port) {
	/** __asm__是ansi标准自带的
	 * asm [volatile] ( AssemblerTemplate
	 *				   : OutputOperands	// 输出寄存器的值到变量
	 *				   [ : InputOperands	// 输入变量的值到寄存器
	 *				   [ : Clobbers ] ])
	 */
	u8 ret;
	asm volatile("in %%dx, %%al" : "=a"(ret) :  "d"(port));
	return ret;
}

/** 从IO端口写入8位数据。
 * @param port 端口
 * @param data 需要写的数据
 */
void port_byte_out(u16 port, u8 data) {
	asm volatile("out %%al, %%dx" : :"a"(data), "d"(port));
}

/** 从IO端口读取16位数据。
 * @param port 端口
 * @return 读取的数据。
 */
u16 port_word_in(u16 port) {
	u16 ret;
	asm volatile("in %%dx, %%ax" : "=a"(ret) : "d"(port));
	return ret;
}

/** 从IO端口写入16位数据。
 * @param port 端口
 * @param data 需要写的数据
 */
void port_word_out(u16 port, u16 data) {
	asm volatile("out %%ax, %%dx" : : "a"(port), "d"(data));
}
