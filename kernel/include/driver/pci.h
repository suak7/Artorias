#ifndef PCI_H
#define PCI_H

#include <stdint.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

#define PCI_VENDOR_ID 0x00             // Identifies the manufacturer (0xFFFF = no device)
#define PCI_CLASS_INFO 0x08            // Contains class, subclass, and prog if
#define PCI_SUBCLASS 0x0A              // Specific device category
#define PCI_HEADER_TYPE 0x0E           // Determines if the device is single/multi-function
#define PCI_CLASS_SERIAL 0x0C          // Base class for serial bus controllers
#define PCI_SUBCLASS_USB 0x03          // Subclass for USB controllers

// Holds the physical memory address (MMIO) where the 
// EHCI controller's operational registers are mapped
#define PCI_BAR0 0x10

#define EHCI_CAPLENGTH 0x00            // Used to find operational registers
#define EHCI_HCSPARAMS 0x04            // Number of ports

#define EHCI_USBCMD 0x00               // Used to start/stop/reset the host controller
#define EHCI_USBSTS 0x04               // Reports interrupts and hardware errors

#define EHCI_PORTSC_BASE 0x44          // Start of the array of port registers
#define EHCI_PORTSC_CCS (1 << 0)       // Current connect status (1 = Device is present)
#define EHCI_PORTSC_PED (1 << 2)       // Port enabled/disabled
#define EHCI_PORTSC_PR (1 << 7)        // Port reset: used to begin device enumeration
#define EHCI_PORTSC_PO (1 << 12)       // Port owner (1 = companion controller (USB 1.1))
#define EHCI_PORTSC_PP (1 << 13)       // Port power: controls VBUS to the port

uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void pci_print_device_info(uint8_t bus, uint8_t slot, uint8_t func, uint32_t id, uint8_t class_code, uint8_t subclass, uint8_t prog_if);
void pci_check_device(uint8_t bus, uint8_t slot, uint8_t func);
void pci_enumerate(void);

#endif