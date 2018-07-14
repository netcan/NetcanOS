/*************************************************************************
	> File Name: libc/stdio.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-09 Mon 10:00:51 CST
 ************************************************************************/

#include <video_terminal.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define is_digit(x) ((x) >= '0' && (x) <= '9')

typedef enum {
	ZEROPAD =	0x01,		//!< 用0填充
	SIGN	=	0x01 << 1,	//!< 是否有符号
	LEFT	=	0x01 << 2,	//!< 左对齐
	BASESIGN	=	0x01 << 3,	//!< 显示0x
	LOWER	=	0x01 << 4,	//!< 16进制是否小写
	SPACE	=	0x01 << 5,	//!< 在正数前面加一个空格
	PLUS	=	0x01 << 6,	//!< 显示加号
} FLAG;

static char * num_to_str(char *str, int num, int base, int width, int precision, int flags) {
	char sign = 0,
		 *digits = "0123456789ABCDEFX",
		 tmp[64]; // 存放进制转换后的数
	if(base < 2 || base > 16) return NULL;

	if(num >= 0) sign = (flags & SPACE) ? ' ': (flags & PLUS) ? '+' : 0;
	else {
		sign = (flags & (SPACE | SIGN)) ? '-' : 0;
		num = -num;
	}

	if(flags & LEFT) flags &= ~ZEROPAD;

	if(flags & LOWER) digits = "0123456789abcdefx";

	if(flags & BASESIGN) {
		if(base == 8) --width;
		else if(base == 16) width -= 2;
	}
	if(sign) --width;

	int i = 0;
	if(num == 0) tmp[i++] = '0';
	else while(num) {
		tmp[i++] = digits[num % base];
		num /= base;
	}
	// 若precision < i，就补0在前面
	if(i > precision) precision = i;
	width -= precision;

	if(! (flags & (LEFT | ZEROPAD))) // 右对齐
		while(width --> 0) *str++ = ' ';
	if(sign) *str++ = sign;
	if(flags & BASESIGN) {
		if(base == 8) *str++ = '0';
		else if(base == 16) {
			*str++ = '0';
			*str++ = digits[16]; // x
		}
	}
	if(! (flags & LEFT)) // 前导0
		while(width --> 0) *str++ = '0';
	while(i < precision--) *str++ = '0';
	while(i--) *str++ = tmp[i];
	while(width-->0) *str++ = ' ';	// 右对齐

	return str;
}

static int read_num(const char **str) { // 返回数字
	int num = 0;
	while(is_digit(**str)) num = num * 10 +  *((*str)++) - '0';
	return num;
}

/** 格式化输出字符串。
 * @param str 输出字符串缓冲区
 * @param fmt 格式
 * @param args 参数列表
 * @return 成功就返回输出字符的字符个数，否则返回负数
 */
int vsprintf(char * str, const char * fmt, va_list args) {
	char *sp = str;
	char buf[128];
	for(; *fmt; ++fmt) {
		if(*fmt != '%') {
			*str++ = *fmt;
			continue;
		}
		int flags = 0, width = 0, precision = -1;
		// 处理flags
		for(++fmt; *fmt; ++fmt) { // 跳过%
			if(*fmt == '-') { flags |= LEFT; continue; }
			if(*fmt == '+') { flags |= PLUS; continue; }
			if(*fmt == ' ') { flags |= SPACE; continue; }
			if(*fmt == '#') { flags |= BASESIGN; continue; }
			if(*fmt == '0') { flags |= ZEROPAD; continue; }
			break;
		}
		// 处理width
		if(is_digit(*fmt))  // 数字
			width = read_num(&fmt);
		else if(*fmt == '*') { // 从参数中读取
			width = va_arg(args, int);
			if(width < 0) {
				width = -width;
				flags |= LEFT;
			}
			++fmt;
		}
		// 处理.precision
		if(*fmt == '.') {
			++fmt;
			if(is_digit(*fmt)) precision = read_num(&fmt);
			else if(*fmt == '*') precision = va_arg(args, int);
			if(precision < 0) precision = 0;
		}

		// 参数类型
		const char *s;
		int len = 0, *p;
		switch(*fmt) {
			case 'c': // 字符
				if(! (flags & LEFT)) while(--width > 0) *str++ = ' '; // 右对齐
				*str++ = (unsigned char) va_arg(args, int); // 因为x86栈元素固定大小为一个字长，即int长度(pushl/popl)
				while(--width > 0) *str++ = ' '; // 左对齐
				break;
			case 's':
				s = va_arg(args, char *);
				len = strlen(s);
				if(precision < 0) precision = len;
				else if(len > precision) len = precision; // 截断

				if(! (flags & LEFT)) while(len < width--) *str++ = ' '; // 右对齐
				for(int i = 0; i < len; ++i) *str++ = *s++;
				while(len < width--) *str++ = ' '; // 左对齐
				break;

			case 'o':
				str = num_to_str(str, va_arg(args, unsigned long), 8, width, precision, flags);
				break;
			case 'p':
				if(width == 0) {
					width = 8 + 2;
					flags |= ZEROPAD;
					flags |= BASESIGN;
				}
				str = num_to_str(str, (unsigned long)va_arg(args, void*), 16, width, precision, flags);
				break;
			case 'x':
				flags |= LOWER;
			case 'X':
				str = num_to_str(str, va_arg(args, unsigned long), 16, width, precision, flags);
				break;

			case 'i':
			case 'd':
				flags |= SIGN;
			case 'u':
				str = num_to_str(str, va_arg(args, unsigned long), 10, width, precision, flags);
				break;
			case 'n': // 将目前写入的字符数写进参数中
				p = va_arg(args, int *);
				*p = str - sp;
				break;
			default:
				if(*fmt) *str++ = *fmt;
				else --fmt;
				break;
		}
	}
	*str = 0;
	return sp - str;
}

/** 格式化输出。
 * @param fmt 格式
 * @param ... 参数列表
 * @return 成功就返回输出字符的字符个数，否则返回负数
 */
int printf(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buffer[512];
	int cnt = vsprintf(buffer, fmt, args);
	print(buffer);
	return cnt;
}
