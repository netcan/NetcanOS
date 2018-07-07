/*************************************************************************
	> File Name: kernel/kernel.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-07 Sat 21:57:42 CST
 ************************************************************************/

void main() {
	// 显存地址
	char* const vram_address = (char*)0x8000;
	*vram_address = 'X';
}
