#include <stdint.h>
#include "ports.h"
#include "driver/serial.h"

/**
 * @brief Checks if the Transmit Holding Register (THR) is empty.
 * We cannot push data to the UART faster than the baud rate allows. 
 * Checking bit 5 of the Line Status Register (LSR) ensures the hardware 
 * is ready for the next byte, preventing data overwrite.
 */
static inline bool is_transmit_empty()
{
    return (inb(COM1 + 5) & 0x20) != 0;
}

/**
 * @brief Initializes the COM1 serial port.
 * The UART hardware starts in an undefined state. We must manually 
 * configure the baud rate, word length, and parity to match our terminal emulator.
 */
int serial_init()
{
    outb(COM1 + 1, 0x00);         // Disable all interrupts
    
    // To set the baud rate, we must enable the Divisor Latch Access Bit (DLAB).
    // This makes ports +0 and +1 refer to the divisor registers instead of data.
    outb(COM1 + 3, 0x80);         // Enable DLAB (set bit 7)

    // Set divisor to 3 (lo-byte 0x03, hi-byte 0x00)
    // Formula: 115200 / 3 = 38400 baud
    // 38400 is a safe high speed for most serial-to-USB adapters.
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);

    // 0x03 (00000011B) sets 8 bits, no parity, one stop bit (8N1)
    // This also clears DLAB, returning ports +0 and +1 to normal operation.
    outb(COM1 + 3, 0x03);

    outb(COM1 + 2, 0xC7);         // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 4, 0x0B);         // IRQs enabled, RTS/DSR set
    
    // Before trusting the serial port for kernel logs, we perform a 
    // loopback test to ensure the UART chip is actually functional.
    outb(COM1 + 4, 0x1E);         // Set in loopback mode, test serial chip
    outb(COM1 + 0, 0xAE);         // Send test byte 0xAE

    // If the byte received isn't the one we sent, the hardware is faulty.
    if (inb(COM1 + 0) != 0xAE)
    {
        return 1;
    }

    // If test passed, set to normal operation mode (not-loopback).
    outb(COM1 + 4, 0x0F);
    return 0;
}

void serial_write_char(char c) 
{
    // Blocking wait: Essential to ensure the hardware is ready.
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

/**
 * @brief Prints a 32-bit value in hexadecimal.
 * Crucial for EHCI debugging to view memory addresses and PCI capability 
 * pointers. We use a local buffer to avoid multiple serial_print calls.
 */
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