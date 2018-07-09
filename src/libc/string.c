/*************************************************************************
	> File Name: libc/string.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 14:17:16 CST
 ************************************************************************/
#include <stddef.h>

/** 从源src所指的内存地址的起始位置开始拷贝count个字节到目标dest所指的内存地址的起始位置中。
 * @param src 源内存地址
 * @param dest 目标内存地址
 * @param count 拷贝的字节数
 * @return 目标内存地址
 */
void* memcpy( void *dest, const void *src, size_t count ) {
    const u8 *sp = src;
    u8 *dp = dest;
    while(count--) *dp++ = *sp++;
    return dest;
}

/** 将s所指向的某一块内存中的后n个字节的内容全部设置为c指定的ASCII值。
 * @param s 需要写的内存地址
 * @param c 需要写入的内容
 * @param n 写入的长度
 * @return 返回s
 */
void *memset(void *s, int c, size_t n) {
    u8 *sp = s;
    while(n--) *sp++ = (u8)c;
    return s;
}

/** 返回字符串str的长度
 * @param str 字符串
 * @return 长度
 */
size_t strlen(const char *str) {
	size_t len = 0;
	for(; str[len]; ++len);
	return len;
}
