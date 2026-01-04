#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define DARK_GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW 0xE
#define WHITE 0xF

/**
 * This is the VGA attribute byte bitfield.
 * In VGA text mode, every character on the screen is represented by 
 * two bytes in memory: the ASCII character and its attribute (color). 
 * (bg) << 4: Shifts the 4-bit background color into the upper nibble.
 * | (fg): Combines it with the 4-bit foreground color in the lower nibble.
 */
#define VGA_COLOR(fg, bg) (((bg) << 4) | (fg))
#define WHITE_ON_BLACK VGA_COLOR(WHITE, BLACK)

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void clear_screen(void);
void vga_init(void);
void vga_print(const char* str);
void vga_print_hex(uint32_t value);
void vga_print_hex8(uint8_t value);
void vga_print_color(const char* str, uint8_t fg, uint8_t bg);

#endif