/*************************************************************************
	> File Name: drivers/video_terminal.h
	  > Author: Netcan
	  > Blog: http://www.netcan666.com
	  > Mail: 1469709759@qq.com
	  > Created Time: 2018-07-08 Sun 11:57:51 CST
 ************************************************************************/

#ifndef VIDEO_TERMINAL_H
#define VIDEO_TERMINAL_H
// 机器启动后，图像硬件初始为VGA文本模式（另一种模式为图像模式），能显示80x25个字符，用2个字节表示一个字符。
// 显存地址
#define VRAM_ADDRESS 0xb8000
#define MAX_ROW 25
#define MAX_COL 80
// 黑底白字
#define WHITE_ON_BLACK 0x0f
/* 屏幕设备的IO端口
REG_SCREEN_CTRL 写入14，获取偏移量的高字节
REG_SCREEN_CTRL 写入15，获取偏移量的低字节
*/
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

extern unsigned char *VRAM;
// 清屏
void clear_vt(void);

// 在第row行，第col列打印属性为attribute_byte的字符character
void print_char(char character, int row, int col, char attribute_byte);

// 在第row行，第col列打印字符串
void print_at(const char* string, int row, int col);

// 在当前行打印字符串
void print(const char* string);
#endif

