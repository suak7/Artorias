#include "driver/serial.h"
#include <ports.h>
#include <stdint.h>

static bool serial_initialized = false;

static inline int is_transmit_empty(void) 
{
    return inb(COM1 + 5) & 0x20;
}

bool serial_init(void) 
{
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);

    serial_initialized = true;
}

void serial_write_char(char c) 
{
    if (!serial_initialized) 
    {
        return;
    }
    
    while (!is_transmit_empty());
    outb(COM1, c);
}

void serial_print(const char* str) 
{
    while (*str) 
    {
        serial_write_char(*str++);
    }
}

void serial_print_hex(uint32_t value) 
{
    const char* hex = "0123456789ABCDEF";
    char buf[9];
    buf[8] = '\0';

    for (int i = 7; i >= 0; i--) 
    {
        buf[i] = hex[value & 0xF];
        value >>= 4;
    }

    serial_print(buf);
}

void serial_print_hex8(uint8_t value)
{
    const char* hex = "0123456789ABCDEF";
    char buf[3];
    buf[0] = hex[(value >> 4) & 0xF];
    buf[1] = hex[value & 0xF];
    buf[2] = '\0';
    serial_print(buf);
}