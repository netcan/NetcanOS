/*************************************************************************
	> File Name: libc/stdarg.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 17:46:42 CST
 ************************************************************************/

#ifndef STDARG_H
#define STDARG_H
typedef char* va_list;
#define va_start(ap, pN)	\
	((ap) = ((va_list) (&pN) + __va_argsiz(pN)))
#define va_end(ap)	((void)0)
#define va_arg(ap, t)					\
    (((ap) = (ap) + __va_argsiz(t)),		\
     *((t*) (void*) ((ap) - __va_argsiz(t))))
#define __va_argsiz(t)	\
	(((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
#endif
