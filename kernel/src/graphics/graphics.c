#include "graphics.h"

int cursor_x = 0;
int cursor_y = 0;

void clear_screen(uint32_t color)
{
    for (int y = 0; y < mb_info->framebuffer_height; y++)
    {
        for (int x = 0; x < mb_info->framebuffer_width; x++)
        {
            set_pixel(x, y, color);
        }
    }
}

void set_pixel(int x, int y, uint32_t color)
{
    unsigned *backbuffer = (unsigned *)(mb_info->framebuffer_addr + (y + mb_info->framebuffer_height) * mb_info->framebuffer_pitch);
    backbuffer[x] = color;
}

int get_pixel(int x, int y)
{
    unsigned int *backbuffer = (unsigned int *)(mb_info->framebuffer_addr + (y + mb_info->framebuffer_height) * mb_info->framebuffer_pitch);
    return backbuffer[x];
}

void set_rect(int x, int y, int width, int height, uint32_t color)
{
    for (int i = y; i < y + height; i++)
    {
        for (int _i = x; _i < x + width; _i++)
        {
            set_pixel(_i, i, color);
        }
    }
}

void scroll_up()
{
    for (int y = 0; y < mb_info->framebuffer_height - 8; y++)
    {
        for (int x = 0; x < mb_info->framebuffer_width; x++)
        {
            int color = get_pixel(x, y + 8);
            set_pixel(x, y, color);
        }
    }
    set_rect(0, mb_info->framebuffer_height - 8, mb_info->framebuffer_width, 8, 0x300a24);
    flush();
}

void put_char(char c, int x, int y, uint32_t color)
{
    uint8_t *offset = font + sizeof(font_header_t) + 16 * c;

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (offset[i] & (1 << j))
            {
                set_pixel(x + 8 - j, y + i, color);
            }
        }
    }
}

void put_string(char *string, uint32_t color)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == '\n')
        {
            cursor_x = 0;
            cursor_y += CHAR_HEIGHT;
            if (cursor_y >= mb_info->framebuffer_height)
            {
                scroll_up();
                cursor_y -= CHAR_HEIGHT;
            }
        }
        else
        {
            put_char(string[i], cursor_x, cursor_y, color);
            cursor_x += CHAR_WIDTH;
            if (cursor_x >= mb_info->framebuffer_width)
            {
                cursor_x = 0;
                cursor_y += CHAR_HEIGHT;
                if (cursor_y >= mb_info->framebuffer_height)
                {
                    scroll_up();
                    cursor_y -= CHAR_HEIGHT;
                }
            }
        }
    }
}

void flush()
{
    memcpy(mb_info->framebuffer_addr, mb_info->framebuffer_addr + mb_info->framebuffer_height * mb_info->framebuffer_pitch, mb_info->framebuffer_pitch * mb_info->framebuffer_height);
}