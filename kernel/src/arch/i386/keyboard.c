#include <stdint.h>
#include <stdbool.h>
#include <lib/lib.h>
#include <tasking/tasking.h>
#include <graphics/graphics.h>

#define SC_MAX 57
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define UP 0x80 + 0x48

static char key_buffer[256];

const char keyboard_map[] = {
    0,
    27,
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\b',
    '\t',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '\n',
    0,
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '	\'',
    '`',
    0,
    '	\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    0,
    '*',
    0,
    ' ',
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

uint8_t scancode;

void task1(void)
{
    while (true)
    {
        set_rect(75, 75, 425, 425, 0x3f3f3f);
        cursor_x = 75;
        cursor_y = 75;
        put_string("Application 1", 0xffffff);
        set_rect(75, 91, 425, 425, 0x4e4e4e);
        flush();
        
        task_switch();
    }
}

bool backspace(char buffer[])
{
    int len = strlen(buffer);
    if (len > 0)
    {
        buffer[len - 1] = '\0';
        return true;
    }
    else
    {
        return false;
    }
}

void print_backspace()
{
    set_rect(cursor_x - 8, cursor_y, 8, 16, 0x300a24);
    cursor_x -= 8;
}

void vector33_handler(void)
{
    scancode = inb(0x60);
    if (scancode > SC_MAX)
        return;

    if (scancode == BACKSPACE)
    {
        if (backspace(key_buffer) == true)
        {
            print_backspace();
            flush();
        }
    }

    else if (scancode == ENTER)
    {
        cursor_y += 16;
        execute_command(key_buffer);
        key_buffer[0] = '\0';
    }
    else
    {
        char letter = keyboard_map[(int)scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        put_string(str, 0xffffff);
        flush();
    }
}

void print_shell()
{
    put_string("\nroot@moon", 0x008000);
    put_string(":", 0xffffff);
    put_string("-", 0x3a2a4e);
    put_string("$ ", 0xffffff);
    flush();
}

void execute_command(char *input)
{
    if (strcmp(input, "halt") == 0)
    {
        cursor_x = 0;
        put_string("Halting the CPU\n", 0xffffff);
        flush();
        asm volatile("hlt");
    }
    else if (strcmp(input, "help") == 0)
    {
        cursor_x = 0;
        put_string("app1 - run app\nhalt - halt the cpu", 0xffffff);
        flush();
    }
    else if (strcmp(input, "app1") == 0)
    {
        cursor_x = 0;
        put_string("Running app1 task...\n", 0xffffff);
        flush();
        add_task(task1);
        start_multitasking();
    }
    else
    {
        cursor_x = 0;
        put_string("Unknown command: ", 0xffffff);
        put_string(input, 0xffffff);
        flush();
    }

    print_shell();
}
