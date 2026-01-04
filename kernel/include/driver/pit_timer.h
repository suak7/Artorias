#ifndef PIT_TIMER_H
#define PIT_TIMER_H

#include <stdint.h>

// I/O Port for channel 0 data (connected to IRQ0)
// This is where you load the value to count.
#define PIT_CHANNEL_0 0x40 

// I/O Port for sending mode/command instructions to PIT chip
// This is where you define how to count.
#define PIT_COMMAND 0x43 

// The internal oscillator frequency is 1.193182 MHz. 
// It is derived from the master clock of the original IBM PC (14.31818 MHz divided by 12).
// This value is used to convert human-readable milliseconds into raw ticks.
#define PIT_BASE_FREQ 1193182 

void pit_wait(uint32_t ms);

#endif