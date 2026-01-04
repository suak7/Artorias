#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * This is the  COM port base address.
 * COM1 is the primary serial interface for x86 systems. 
 * 0x3F8 is the industry-standard I/O port address for the first communication port.
 * In a custom kernel, serial output is critical for headless debugging, 
 * allowing you to stream EHCI register logs and status updates to a 
 * separate terminal via a null-modem cable or emulator pipe.
 */
#define COM1 0x3F8

int serial_init();
void serial_write_char(char c);
void serial_print(const char* str);
void serial_print_hex(uint32_t value);
void serial_print_hex8(uint8_t value);

#endif