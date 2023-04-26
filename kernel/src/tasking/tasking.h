#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
// #include <memory/memory.h>
#include <lib/lib.h>

typedef struct
{
    uint8_t *stack_pointer;
    void (*function)(void);
} task_t;

void init_tasks(void);
bool add_task(void (*function)(void));
void task_switch(void);
void close_multitasking(void);
void start_multitasking(void);