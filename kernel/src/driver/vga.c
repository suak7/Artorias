#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "ports.h"
#include "driver/vga.h"

uint8_t vga_attr;
static uint16_t vga_row;
static uint16_t vga_col;

/**
 * @brief Updates the hardware blinking cursor on the screen.
 * The VGA hardware maintains its own internal cursor position. To keep the 
 * visual cursor synchronized with our software vga_row/vga_col, we must 
 * communicate with the CRT Controller (CRTC) registers.
 */
static void update_cursor(int x, int y) 
{
    // The cursor position is a single 16-bit linear index
    // (row * width + column), not a coordinate pair.
    uint16_t pos = y * VGA_WIDTH + x;

    // The CRTC registers are accessed via an index/data port pair.
    // 0x3D4 is the address register (index), and 0x3D5 is the data register.
    outb(0x3D4, 0x0F);            // Select cursor location low register
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);            // Select cursor location high register
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void clear_screen(void) 
{
    // VGA text buffer is mapped to 0xB8000.
    volatile uint16_t* video = (volatile uint16_t*)VIDEO_MEMORY;

    // A blank character consists of the space ASCII code (0x20)
    // combined with the current background/foreground attributes.
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
            // Layout: Attribute byte | Character byte
            // We shift the attribute to the high 8 bits of the 16-bit word.
            const size_t index = vga_row * VGA_WIDTH + vga_col;
            video[index] = (uint16_t)vga_attr << 8 | *str;
            vga_col++;
        }

        if (vga_col >= VGA_WIDTH) 
        {
            vga_col = 0;
            vga_row++;
        }

        // This is to prevent out-of-bounds writes to memory past the VGA buffer.
        // This current logic wraps back to the top of the screen
        // instead of shifting memory up (simpler to implement for early boot).
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
    vga_attr = old;               // Restore original global style
}