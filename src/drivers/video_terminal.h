/*************************************************************************
	> File Name: drivers/video_terminal.h
	> Author: Netcan
	> Blog: http://www.netcan666.com
	> Mail: 1469709759@qq.com
	> Created Time: 2018-07-08 Sun 11:57:51 CST
 ************************************************************************/

#include <io.h>
#ifndef VIDEO_TERMINAL_H
#define VIDEO_TERMINAL_H
#define VRAM_ADDRESS 0xb8000 //!< 显存地址
/**
 * 机器启动后，图像硬件初始为VGA文本模式（另一种模式为图像模式），能显示80x25个字符，用2个字节表示一个字符。
 */
#define MAX_ROW 25
#define MAX_COL 80
#define WHITE_ON_BLACK 0x0f //!< 黑底白字
/** 屏幕设备的IO端口。
 * - REG_SCREEN_CTRL 写入14，控制访问偏移量的高字节
 * - REG_SCREEN_CTRL 写入15，控制访问偏移量的低字节
 * - 读或写REG_SCREEN_DATA来访问偏移量的高低字节。
*/
#define REG_SCREEN_CTRL 0x3d4 //!< 屏幕控制端口
#define REG_SCREEN_DATA 0x3d5 //!< 屏幕数据端口 @see REG_SCREEN_CTRL

#define TABSIZE 8 //!< TAB制表符的长度

extern u8 * const VRAM;
void clear_vt(void);

void print_char(char character, int row, int col, char attribute_byte);

void print_at(const char* string, int row, int col);

void print(const char* string);
#endif

