/*************************************************************************
	> File Name: kernel/heap.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-13 Fri 10:30:53 CST
 ************************************************************************/


#include <io.h>
#ifndef HEAP_H
#define  HEAP_H
extern u32 heap_placement_address; //!< 堆地址，分配内存用
void * kmalloc(u32 sz, s32 aligned, u32* phy_addr);
#endif
