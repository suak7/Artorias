; High-level languages like C expect a specific stack frame and entry 
; sequence that a raw binary load doesn't provide. This file calls the C 
; entry point while providing a safety net if the kernel function ever returns.

[bits 32]
[extern kernel_main]   

global _start           

_start:
    ; We call the kernel rather than jumping to it. This allows the 
    ; compiler to manage the stack normally and ensures that if kernel_main
    ; finishes its execution, the CPU returns here to be safely halted.
    call kernel_main

    ; A kernel should never return because there is no OS or shell 
    ; underneath it to return to. If execution reaches this point, something 
    ; has gone wrong or the system is intended to shut down.
    cli           ; Disable interrupts to prevent wake-ups
    hlt           ; Halt the CPU to reduce power/heat
    jmp $         ; Infinite loop as a final fail-safe if a non-maskable interrupt occurs