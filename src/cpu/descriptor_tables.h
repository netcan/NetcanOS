/*************************************************************************
	> File Name: kernel/descriptor_tables.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-09 Mon 15:30:46 CST
 ************************************************************************/

#include <io.h>
#ifndef DT_H
#define DT_H
#define PIC_MASTER_CONTROL 0x20 //!< master pic的控制端口
#define PIC_MASTER_DATA 0x21	//!< master pic的数据端口
#define PIC_SLAVE_CONTROL 0xa0	//!< slave pic的控制端口
#define PIC_SLAVE_DATA 0xa1		//!< slave pic的数据端口
#define PIC_EOI 0x20	//!< 中断结束信息

/** GDT表结构。
* 1st flags: (present) (privilege) (descriptor type)
* type flags: (code) (conforming) (readable) (accessed)
* 2nd flags: (granularity) (32-bit default) (64-bit seg) (AVL)
*/
struct gdt_entry_struct {
   u16 limit_low;           //!< segment limit(0:15)
   u16 base_low;            //!< base address(0:15)
   u8  base_middle;         //!< base address(16:23)
   u8  access;              //!< 1st flags和type flags
   u8  granularity;			//!< 2nd flags和segment limit(16:19)
   u8  base_high;           //!< base address(24:31)
} __attribute__((packed));	//!< 用packed让gcc不要对齐
typedef struct gdt_entry_struct gdt_entry_t;

/** GDT指针，告诉CPU GDT表的位置。
 */
struct gdt_ptr_struct {
   u16 limit;               //!< GDT表的大小
   u32 base;                //!< GDT表的地址
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

/** IDT表结构
 */
struct idt_entry_struct {
   u16 base_lo;             //!< 中断服务程序向量地址的低16位
   u16 sel;                 //!< 内核段选择（0x08选中代码段）
   u8  always0;             //!< 总是0
   u8  flags;               //!< Flags
   u16 base_hi;             //!< 中断服务程序向量地址的高16位
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

/** IDT表指针，告诉CPU IDT表的位置。
 */
struct idt_ptr_struct {
   u16 limit;		//!< IDT表大小
   u32 base;        //!< IDT表地址
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

void init_descriptor_tables();

/** CPU定义的32个system error中断程序
 */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/** 32-47号中断
 */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


#endif
