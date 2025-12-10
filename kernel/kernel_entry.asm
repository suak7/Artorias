[bits 32]
[extern kernel_main]   

global _start           

_start:
    mov esp, 0x90000
    mov ebp, esp

    call kernel_main

    cli
    hlt
    jmp $