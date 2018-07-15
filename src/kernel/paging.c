/*************************************************************************
  > File Name: kernel/paging.c
  > Author: Netcan
  > Blog: http://www.netcan666.com
  > Mail: 1469709759@qq.com
  > Created Time: 2018-07-13 Fri 16:59:34 CST
 ************************************************************************/

#include <paging.h>
#include <video_terminal.h>
#include <heap.h>
#include <string.h>

u32 *frame_bitset; //!< 页框frame的bitset形式，物理内存
u32 nframes = 0x100000;	//!< 页框数量，假设物理内存4GB大，那么0x100000000 / 0x1000 = 0x100000

static page_directory_t *kernel_directory, *current_directory;

// 将frame的bitset置位
static void set_frame(u32 frame) {
	u32 frame_idx = FRAME_INDEX_FROM_BITSET(frame),
		frame_offset = FRAME_OFFSET_FROM_BITSET(frame);
	frame_bitset[frame_idx] |= (0x1 << frame_offset);
}

// 将frame的bitset清零
static void clear_frame(u32 frame) {
	u32 frame_idx = FRAME_INDEX_FROM_BITSET(frame),
		frame_offset = FRAME_OFFSET_FROM_BITSET(frame);
	frame_bitset[frame_idx] &= ~(0x1 << frame_offset);
}

// 判断frame是否在bitset中
static u32 test_frame(u32 frame) {
	u32 frame_idx = FRAME_INDEX_FROM_BITSET(frame),
		frame_offset = FRAME_OFFSET_FROM_BITSET(frame);
	return (frame_bitset[frame_idx] >> frame_offset) & 0x1;
}

// 找出第一个可用的frame
static u32 first_frame() {
	for(int i = 0; i < FRAME_INDEX_FROM_BITSET(nframes); ++i) {
		if(frame_bitset[i] != 0xFFFFFFFF) {
			for(int j = 0; j < 32; ++j) {
				if( !((frame_bitset[i] >> j) & 0x1))
					return i * sizeof(u32) + j;
			}
		}
	}
	return ~0u;
}

/** 分配页框。
 * @param page 页面
 * @param is_kernel 是否属于内核模式
 * @param is_writeable 是否可写
 * @param frame_addr 若不为~0u，则采用这个地址作为页框地址
 */
void alloc_frame(page_t *page, int is_kernel, int is_writeable, u32 frame) {
	if(page) {
		if(page->available) return;
		else {
			if(frame == ~0u || test_frame(frame)) frame = first_frame();
			ASSERT(frame != ~0u, "no free page frame!");

			set_frame(frame);
			page->frame = frame;
			page->user = is_kernel?0:1;
			page->writeable = is_writeable?1:0;
			page->present = 1;
			page->available = 1;
		}
	}
}

/** 释放页框
 * @param page 页面
 */
void free_frame(page_t *page) {
	if(page && page->available) {
		u32 frame = page->frame;
		clear_frame(frame);
		page->available = 0;
	}
}

/** 初始化分页管理。
*/
void init_paging() {
	frame_bitset = (u32*)kmalloc(FRAME_INDEX_FROM_BITSET(nframes) * sizeof(u32), 0, NULL);
	memset(frame_bitset, 0, FRAME_INDEX_FROM_BITSET(nframes) * sizeof(u32));

	// 为内核目录分配内存
	kernel_directory = (page_directory_t*)kmalloc(sizeof(page_directory_t), 1, NULL);
	memset(kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

	/** 分配页框，使得物理地址和虚拟地址一致，并为已用过的内核空间分配页框。
	 * 由于内核加载到0x1000，后面有VRAM位于0xb8000，并且栈指针位于0x90000，所以覆盖完整个1MB空间。
	 */
	for(u32 i = 0; i < 0x100000; i += 0x1000)
		alloc_frame(get_page(i, 1, kernel_directory), 0, 0, i / 0x1000); // 内核页面不可读


	// 注册页面错误中断处理程序
	register_int_handler(14, &page_fault);

	// 开启分页
	switch_page_directory(kernel_directory);
}

/** 切换页目录。
 * @param dir 页目录指针
 */
void switch_page_directory(page_directory_t *dir) {
	current_directory = dir;
	asm volatile("mov %0, %%cr3":: "r"(&dir->tables_physical));
	u32 cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000; // 开启分页
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

/** 获取页面。
 * @param address 获取页面指针
 * @param make 若为真，表明该页面不在页表中，则创建页表
 * @param dir 页表指针
 * @return 返回页面。
 */
page_t *get_page(u32 address, int make, page_directory_t *dir) {
	u32 frame = (u32)address / 0x1000;
	u32 table_idx = frame / 1024;

	if(dir->tables[table_idx]) // 已分配
		return &dir->tables[table_idx]->pages[frame % 1024];
	else if(make){ // 未创建，创建页表
		u32 phy_addr;
		// 物理内存和虚拟内存地址一样
		dir->tables[table_idx] = (page_table_t*)kmalloc(sizeof(page_table_t), 1, &phy_addr);
		memset(dir->tables[table_idx], 0, sizeof(page_table_t));

		dir->tables_physical[table_idx] = phy_addr | 0x7; // PRESENT, RW, US.
		return &dir->tables[table_idx]->pages[frame % 1024];
	} else return NULL;
}

/** 缺页中断处理程序。
*/
void page_fault(registers_t regs) {
	u32 faulting_address;
	// faulting_address存放于CR2寄存器中
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	int present   = !(regs.err_code & 0x1); // Page not present
	int rw = regs.err_code & 0x2;           // Write operation?
	int us = regs.err_code & 0x4;           // Processor was in user-mode?
	int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
	int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

	printf("Page fault! (");
	if (present) {printf("present ");}
	if (rw) {printf("read-only ");}
	if (us) {printf("user-mode ");}
	if (reserved) {printf("reserved ");}
	printf(") at %p\n", faulting_address);
	ASSERT(0, "Page fault");
}
