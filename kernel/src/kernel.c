#include <kernel.h>
#include "driver/pci.h"
#include "driver/serial.h"
#include "driver/vga.h"

void hcf(void)
{
    for (;;)
    {
        asm("hlt");
    }
}

void kernel_main(void) 
{
    vga_init();
    serial_init();

    serial_print("\n");
    serial_print("Kernel loaded successfully\n");
    serial_print("Scanning PCI bus...\n");
    serial_print("Enumerating PCI devices...\n\n");

    pci_enumerate();

    serial_print("PCI scan complete\n");

    hcf();
}