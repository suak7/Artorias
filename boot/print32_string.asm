[bits 32]

VIDEO_MEMORY equ 0xb8000          
WHITE_ON_BLACK equ 0x0f            

print32_string:
    pushad                          

    mov eax, [cursor_pos]           
    mov edx, VIDEO_MEMORY           
    add edx, eax                    

.print32_loop:
    mov al, [EBX]                   
    cmp al, 0                       
    je .end_print32_loop                        
    
    mov ah, WHITE_ON_BLACK          
    mov [edx], ax                   

    add ebx, 1                      
    add edx, 2                      
    
    jmp .print32_loop                       

.end_print32_loop:
    mov eax, edx                    
    sub eax, VIDEO_MEMORY           
    mov [cursor_pos], eax           
    
    popad                           
    ret