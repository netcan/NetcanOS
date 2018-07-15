/*************************************************************************
	> File Name: kernel/heap.c
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-13 Fri 10:31:25 CST
 ************************************************************************/

#include <heap.h>

extern u32 end; //!< 内核区域结束地址
u32 heap_placement_address = (u32)&end; //!< 堆地址，分配内存用

/** 内核内存分配函数
 * @param sz 分配大小
 * @param aligned 是否4k对齐
 * @param phy 保存物理地址
 * @return 内存分配后的地址
 */
void * kmalloc(u32 sz, s32 aligned, u32* phy_addr) {
	if(aligned && (heap_placement_address & 0xFFFFF000))  // 页面地址4KB对齐
		heap_placement_address = (heap_placement_address & 0xFFFFF000) + 0x1000;
	if(phy_addr) *phy_addr = heap_placement_address;
	void *tmp = (void*)heap_placement_address;
	heap_placement_address += sz;
	return tmp;
}

