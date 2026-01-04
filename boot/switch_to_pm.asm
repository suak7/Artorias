; To access the full 4GB of RAM and utilize 32-bit registers for EHCI 
; controller structures (which often reside in high memory), we must exit 
; the 1MB limit of real mode.

[bits 16]

switch_to_pm:
    ; Interrupts must be disabled during the switch.
    ; The real mode interrupt vector table is incompatible with 
    ; protected mode. Keeping if=1 would cause a triple fault on any interrupt.
    cli  

    ; Load the GDT register with the location/size 
    ; of our table defined in gdt.asm
    lgdt [gdt_descriptor]      

    ; Setting bit 0 (protection enable) toggles the CPU's mode
    mov eax, cr0               
    or eax, 0x1               
    mov cr0, eax               

    ; The CPU uses a pipeline to pre-fetch instructions. Even after 
    ; setting CR0, the pipeline may contain 16-bit decoded instructions. 
    ; A far jump flushes the pipeline and forces the CPU to decode the 
    ; following code using the new 32-bit GDT selectors.
    jmp CODE_SEG:init_pm

[bits 32]

; Now in 32-bit mode, we must re-initialize all segment registers.
; In a flat memory model, these all point to the same 4GB DATA_SEG.
init_pm:
    mov ax, DATA_SEG            
    mov ds, ax                  
    mov ss, ax                  
    mov es, ax                 
    mov fs, ax                  
    mov gs, ax                  

    ; Update the stack to a safe, high-memory area. 
    ; 0x90000 is a common choice as it sits safely below the BIOS/VGA 
    ; reserved areas but well above our bootloader code.
    mov ebp, 0x90000            
    mov esp, ebp               

    call begin_pm               