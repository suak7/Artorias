[bits 32]

VIDEO_MEMORY equ 0xb8000       ; vga text mode buffer       
WHITE_ON_BLACK equ 0x0f            

print32_string:
    pushad                     ; save all 32-bit registers                

    mov eax, [cursor_pos]      ; load current position offset       
    mov edx, VIDEO_MEMORY      ; base address of video memory      
    add edx, eax               ; edx = video memory + offset     

.print32_loop:
    mov al, [ebx]              ; load character from string                  
    cmp al, 0                       
    je .end_print32_loop                        
    
    mov ah, WHITE_ON_BLACK          
    mov [edx], ax              ; write char (al) and color (ah)                

    add ebx, 1                 ; next character in string           
    add edx, 2                 ; next position (2 bytes per char)      
    
    jmp .print32_loop                       

.end_print32_loop:
    mov eax, edx               ; current video memory address     
    sub eax, VIDEO_MEMORY      ; convert to offset from start     
    mov [cursor_pos], eax      ; save for next print       
    
    popad                           
    ret