/*************************************************************************
	> File Name: libc/string.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 14:17:16 CST
 ************************************************************************/
#include <stddef.h>

void* memcpy( void *dest, const void *src, size_t count ) {
    const char *sp = src;
    char *dp = dest;
    while(count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *s, int c, size_t n) {
    char *sp = s;
    while(n--) *sp++ = (unsigned char)c;
    return s;
}
