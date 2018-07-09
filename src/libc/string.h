/*************************************************************************
	> File Name: libc/string.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 14:00:23 CST
 ************************************************************************/

#ifndef STRING_H
#define STRING_H
#include <stddef.h>
void* memcpy( void *dest, const void *src, size_t count );
void* memset(void *s, int c, size_t n);
int strlen(const char *str);
#endif
