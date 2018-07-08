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
/** 格式化输出字符串。
 * @param str 输出字符串缓冲区
 * @param fmt 格式
 * @param arg 参数列表
 * @return 成功就返回输出字符的字符个数，否则返回负数
 */
int vsprintf(char * str, const char * fmt, va_list arg);

#endif
