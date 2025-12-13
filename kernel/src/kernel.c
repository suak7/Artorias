#define VIDEO_MEMORY 0xb8000
#define WHITE_ON_BLACK 0x0f

void print(const char* str, int row) {
    char* video = (char*)VIDEO_MEMORY;
    video += row * 160;  
    
    int i = 0;
    while (str[i] != '\0') {
        video[i * 2] = str[i];      
        video[i * 2 + 1] = WHITE_ON_BLACK;  
        i++;
    }
}

void clear_screen(void) {
    char* video = (char*)VIDEO_MEMORY;
    
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = WHITE_ON_BLACK;
    }
}

void kernel_main(void) {
    clear_screen();
    
    print("Kernel loaded successfully", 0);
    print("Ready to implement PCI enumeration", 1);
    
    while (1) {
        __asm__ __volatile__("hlt");
    }
}