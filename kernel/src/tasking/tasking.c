#include "tasking.h"

#define STACK_SIZE 1024
#define MAX_TASKS 10

static task_t *current_task;
static task_t task_list[MAX_TASKS];
static uint8_t task_count = 0;

void init_tasks(void)
{
    task_count = 0;
}

bool add_task(void (*function)(void))
{
    if (task_count == MAX_TASKS)
    {
        return false;
    }

    task_list[task_count].function = function;
    task_list[task_count].stack_pointer = (uint8_t *)malloc(STACK_SIZE);

    if (!task_list[task_count].stack_pointer)
    {
        return false;
    }

    task_list[task_count].stack_pointer += STACK_SIZE - sizeof(uint32_t);
    *((uint32_t *)task_list[task_count].stack_pointer) = (uint32_t)function;
    task_count++;
    return true;
}

void task_switch(void)
{
    asm volatile("pushal");
    asm volatile("mov %%esp, %0"
                 : "=r"(current_task->stack_pointer));
    asm volatile("popal");

    current_task++;
    if (current_task == &task_list[task_count])
    {
        current_task = &task_list[0];
    }

    asm volatile("pushal");
    asm volatile("mov %0, %%esp"
                 :
                 : "r"(current_task->stack_pointer));
    asm volatile("popal");

    asm volatile("jmp *%0"
                 :
                 : "r"(current_task->function));
}

void close_multitasking(void)
{
    for (uint8_t i = 0; i < task_count; i++)
    {
        free(task_list[i].stack_pointer - (STACK_SIZE - sizeof(uint32_t)));
    }

    task_count = 0;
}

void start_multitasking(void)
{
    current_task = &task_list[0];
    asm volatile("mov %0, %%esp"
                 :
                 : "r"(current_task->stack_pointer));
    current_task->function();
}
