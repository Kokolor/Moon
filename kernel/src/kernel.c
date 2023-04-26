#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <multiboot/boot_info.h>
#include <arch/i386/gdt.h>
#include <graphics/graphics.h>
#include <tasking/tasking.h>
#include <arch/i386/idt.h>

void _kstart(multiboot_info_t *mboot_info)
{
    mb_info = mboot_info;
    clear_screen(0x300a24);
    init_idt();
    init_pic();
    init_gdt();
    init_tasks();
    init_mm(mb_info);
    E9_print("\033[0;33m[MoonKernel]\033[0;36m: \033[0;32mGDT Loaded.\n");
    E9_print("\033[0;33m[MoonKernel]\033[0;36m: \033[0;32mTSS Loaded.\n");
    E9_print("\033[0;33m[MoonKernel]\033[0;36m: \033[0;32mIDT Loaded.\n");
    E9_print("\033[0;33m[MoonKernel]\033[0;36m: \033[0;32mMM Loaded.\n");
    E9_print("\033[0;33m[MoonKernel]\033[0;36m: \033[0;32mPIC Enabled.\n");
    sti;
    E9_print("\033[0;33m[MoonKernel]\033[0;36m: \033[0;32mInterrupts Enabled.\n");
    put_string("root@moon", 0x008000);
    put_string(":", 0xffffff);
    put_string("-", 0x3a2a4e);
    put_string("$ ", 0xffffff);
    flush();

    while (1)
        ;
}