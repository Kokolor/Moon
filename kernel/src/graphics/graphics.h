#include <stdint.h>
#include <multiboot/multiboot.h>
#include <memory/memory.h>
#include <lib/lib.h>
#include "font.h"

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

extern int cursor_x;
extern int cursor_y;

void clear_screen(uint32_t color);
void set_pixel(int x, int y, uint32_t color);
int get_pixel(int x, int y);
void set_rect(int x, int y, int width, int height, uint32_t color);
void put_char(char c, int x, int y, uint32_t color);
void put_string(char *string, uint32_t color);
void flush();