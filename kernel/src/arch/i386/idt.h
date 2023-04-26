#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <lib/lib.h>

#define IDTBASE  0x800
#define IDTSIZE  0xFF

#define INTGATE  0x8E00
#define TRAPGATE 0xEF00

struct idt_entry {
	uint16_t offset0_15;
	uint16_t select;
	uint16_t type;
	uint16_t offset16_31;
} __attribute__ ((packed));

struct idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

void init_idt(void);
void init_pic(void);
