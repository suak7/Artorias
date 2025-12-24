#include <kernel.h>
#include <stdint.h>
#include <stddef.h>
#include <ports.h>
#include "driver/vga.h"

uint8_t vga_attr;
static uint16_t vga_row;
static uint16_t vga_col;

static void update_cursor(int x, int y) 
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void clear_screen(void) 
{
    volatile uint16_t* video = (volatile uint16_t*)VIDEO_MEMORY;
    uint16_t blank = (uint16_t)WHITE_ON_BLACK << 8 | ' ';
    
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) 
    {
        video[i] = blank;
    }
    
    vga_row = 0; 
    vga_col = 0; 
    update_cursor(0, 0);
}

void vga_init(void) 
{
    vga_row = 0;
    vga_col = 0;
    vga_attr = VGA_COLOR(WHITE, BLACK);
    clear_screen();
}

void vga_print(const char* str) 
{
    volatile uint16_t* video = (volatile uint16_t*)VIDEO_MEMORY;

    while (*str) 
    {
        if (*str == '\n') 
        {
            vga_col = 0;
            vga_row++;
        }
        else
        {
            const size_t index = vga_row * VGA_WIDTH + vga_col;
            video[index] = (uint16_t)vga_attr << 8 | *str;
            vga_col++;
        }

        if (vga_col >= VGA_WIDTH) 
        {
            vga_col = 0;
            vga_row++;
        }

        if (vga_row >= VGA_HEIGHT) 
        {
            vga_row = 0; 
        }
        
        str++;
    }

    update_cursor(vga_col, vga_row);
}

void vga_print_hex(uint32_t value) 
{
    static const char hex[] = "0123456789ABCDEF";
    char buf[9];
    buf[8] = '\0';
    
    for (int i = 7; i >= 0; i--) 
    {
        buf[i] = hex[value & 0xF];
        value >>= 4;
    }
    
    vga_print(buf);
}

void vga_print_hex8(uint8_t value) 
{
    static const char hex[] = "0123456789ABCDEF";
    char buf[3];

    buf[0] = hex[(value >> 4) & 0xF];
    buf[1] = hex[value & 0xF];
    buf[2] = '\0';

    vga_print(buf);
}

void vga_print_color(const char* str, uint8_t fg, uint8_t bg) 
{
    uint8_t old = vga_attr;
    vga_attr = VGA_COLOR(fg, bg);
    vga_print(str);
    vga_attr = old;
}