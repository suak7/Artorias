#ifndef KERNEL_H
#define KERNEL_H

/**
 * This is the VGA text buffer base address.
 * In x86 systems, the memory range starting at 0xB8000 is architecturally 
 * reserved for the VGA color text buffer. By mapping this address, the kernel 
 * can bypass BIOS interrupts (which are unavailable in protected mode) and 
 * write characters directly to the screen. This is also a Memory-Mapped I/O 
 * (MMIO) region. Writing a character to this memory immediately updates the 
 * corresponding pixel data on the physical display.
 */
#define VIDEO_MEMORY 0xB8000

void hcf(void);

#endif 