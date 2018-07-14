/*************************************************************************
	> File Name: kernel/paging.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-13 Fri 16:59:08 CST
 ************************************************************************/

#include <io.h>
#include <int_handler.h>
#ifndef PAGING_H
#define PAGING_H
#define FRAME_INDEX_FROM_BITSET(addr) ((addr) / 32)
#define FRAME_OFFSET_FROM_BITSET(addr)	((addr) % 32)

/** 分页页面数据结构。
 */

typedef struct {
	u32 present			:1; //!< 当前页面是否位于内存
	u32 writeable		:1;	//!< 是否可写
	u32 user			:1;	//!< 是否属于用户模式
	u32 reversed_lo		:2;	//!< CPU内部保留用
	u32 accessed		:1;	//!< 是否被CPU访问过
	u32 dirty			:1;	//!< 是否被CPU写过
	u32 reversed_hi		:2;	//!< CPU内部保留用
	u32 available		:3;	//!< 未使用，可供内核使用，本内核用来判断是否分配了页框
	u32 frame			:20;//!< 页框号，也就是帧地址/0x1000
} page_t;

/** 页表（二级页表）。
 */
typedef struct {
	page_t pages[1024]; //!< 每个页表包含1k个页面
} page_table_t;


/** 页目录（一级页表）。
 */
typedef struct {
	page_table_t *tables[1024];	//!< 页表指针，虚拟内存用
	u32 tables_physical[1024];	//!< 上述页表的物理地址，写进CR3寄存器生效
	u32 physical_address; //!< 页目录的物理地址，告诉CPU页目录位置，区分页目录用
} page_directory_t;

void init_paging();
void switch_page_directory(page_directory_t *dir);
page_t *get_page(u32 address, int make, page_directory_t *dir);
void page_fault(registers_t regs);
void alloc_frame(page_t *page, int is_kernel, int is_writeable, u32 frame_addr);
void free_frame(page_t *page);
#endif
