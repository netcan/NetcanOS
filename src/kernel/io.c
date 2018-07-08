/*************************************************************************
	> File Name: kernel/io.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 11:26:07 CST
 ************************************************************************/

// in 指令，从IO端口读取数据
unsigned char port_byte_in(unsigned short port) {
	// __asm__是ansi标准自带的
	/* asm [volatile] ( AssemblerTemplate
						: OutputOperands	// 输出寄存器的值到变量
						[ : InputOperands	// 输入变量的值到寄存器
						[ : Clobbers ] ])
	*/
	unsigned char ret;
	__asm__("in %%dx, %%al" : "=a"(ret) :  "d"(port));
	return ret;
}

// out 指令，往IO端口输出数据
void port_byte_out(unsigned short port, unsigned char data) {
	__asm__("out %%al, %%dx" : :"a"(data), "d"(port));
}

unsigned short port_word_in(unsigned short port) {
	unsigned short ret;
	__asm__("in %%dx, %%ax" : "=a"(ret) : "d"(port));
	return ret;
}

void port_word_out(unsigned short port, unsigned short data) {
	__asm__("out %%ax, %%dx" : : "a"(port), "d"(data));
}
