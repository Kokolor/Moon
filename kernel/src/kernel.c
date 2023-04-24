#include <stdint.h>
#include <stddef.h>
#include <limine/limine.h>
#include <arch/x86_64/gdt.h>

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0};

void _start(void)
{
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    init_gdt();

    int width = framebuffer->width;
    int height = framebuffer->height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t color = (0xFF000000) |
                ((x * 255 / width) << 16) |
                ((y * 255 / height) << 8) |
                ((x + y) % 255);
            uint32_t *fb = framebuffer->address;
            fb[y * width + x] = color;

        }
    }

    while (1)
        ;
}
