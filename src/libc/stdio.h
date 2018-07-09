/*************************************************************************
	> File Name: libc/stdio.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 19:57:51 CST
 ************************************************************************/

#include <stdarg.h>
#ifndef STDIO_H
#define STDIO_H
int vsprintf(char * str, const char * fmt, va_list arg);
int printf(const char *fmt, ...);

#endif
