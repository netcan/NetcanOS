/*************************************************************************
	> File Name: kernel/kernel.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-07 Sat 21:57:42 CST
 ************************************************************************/

#include <video_terminal.h>
#include <stdio.h>

/**
 * 内核入口。
 */
void main() {
	printf("Hello World! From NetcanOS\n");
	for(int i = 1; i <= 9; ++i) {
		for(int j = 1; j <= i; ++j)
			printf("%dx%d=%2d\t", i, j, i * j);
		printf("\n");
	}
}
