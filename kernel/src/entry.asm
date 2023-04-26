bits    32
section .multiboot
align 4

multiboot_header:
    dd 0x1BADB002
    dd 0x04
    dd -(0x1BADB002 + 0x04)
   
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    
    dd 0
    dd 32
       
global start
extern _kstart
start:
    mov esp, stack.end
    push ebx
    call _kstart
    pop ebx

    hlt

stack: resb 4096
.end: