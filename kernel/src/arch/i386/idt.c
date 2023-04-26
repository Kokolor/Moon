#include <graphics/graphics.h>
#include "idt.h"

void vector0(void);
void vector32(void);
void vector33(void);

struct idt_ptr idt_pointer;
struct idt_entry idt[IDTSIZE];

void idt_set_gate(uint16_t select, uint32_t offset, uint16_t type, struct idt_entry *descriptor)
{
    descriptor->offset0_15 = (offset & 0xffff);
    descriptor->select = select;
    descriptor->type = type;
    descriptor->offset16_31 = (offset & 0xffff0000) >> 16;
    return;
}

void init_idt(void)
{
    int i;

    for (i = 0; i < IDTSIZE; i++)
        idt_set_gate(0x08, (uint32_t)vector0, INTGATE, &idt[i]);

    idt_set_gate(0x08, (uint32_t)vector32, INTGATE, &idt[32]);
    idt_set_gate(0x08, (uint32_t)vector33, INTGATE, &idt[33]);

    idt_pointer.limit = IDTSIZE * 8;
    idt_pointer.base = IDTBASE;

    memcpy((char *)idt_pointer.base, (char *)idt, idt_pointer.limit);

    asm("lidtl (idt_pointer)");
}

void init_pic(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x70);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void vector0_handler(void)
{
}

void vector32_handler(void)
{
    static int tic = 0;
    static int sec = 0;
    tic++;
    if (tic % 100 == 0)
    {
        sec++;
        tic = 0;
    }
}