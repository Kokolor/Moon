#include "lib.h"
#include <stdbool.h>

void *memcpy(char *dst, char *src, int n)
{
    char *p = dst;
    while (n--)
        *dst++ = *src++;
    return p;
}

void *memset(void *s, int c, size_t n)
{
    uint8_t *p = (uint8_t *)s;

    for (size_t i = 0; i < n; i++)
    {
        p[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n)
{
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    if (src > dest)
    {
        for (size_t i = 0; i < n; i++)
        {
            pdest[i] = psrc[i];
        }
    }
    else if (src < dest)
    {
        for (size_t i = n; i > 0; i--)
        {
            pdest[i - 1] = psrc[i - 1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (size_t i = 0; i < n; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

unsigned char inb(unsigned short port)
{
    unsigned char value;
    asm volatile("inb %1, %0"
                 : "=a"(value)
                 : "Nd"(port));
    return value;
}

void outb(unsigned short port, unsigned char value)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(value), "Nd"(port));
}

unsigned short inw(unsigned short port)
{
    unsigned short value;
    asm volatile("inw %1, %0"
                 : "=a"(value)
                 : "Nd"(port));
    return value;
}

void outw(unsigned short port, unsigned short value)
{
    asm volatile("outw %0, %1"
                 :
                 : "a"(value), "Nd"(port));
}

void delay(uint32_t ms)
{
    uint32_t count = ms * 1193;
    outb(0x43, 0x36);
    outb(0x40, count & 0xFF);
    outb(0x40, (count >> 8) & 0xFF);
    while (inb(0x40) & 0x80)
        ;
}

void itoa(char *buf, unsigned long int n, int base)
{
    unsigned long int tmp;
    int i, j;

    tmp = n;
    i = 0;

    do
    {
        tmp = n % base;
        buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
    } while (n /= base);
    buf[i--] = 0;

    for (j = 0; j < i; j++, i--)
    {
        tmp = buf[j];
        buf[j] = buf[i];
        buf[i] = tmp;
    }
}

int strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
    {
        ++i;
    }
    return i;
}

int strcmp(char s1[], char s2[])
{
    int i;
    for (i = 0; s1[i] == s2[i]; i++)
    {
        if (s1[i] == '\0')
            return 0;
    }
    return s1[i] - s2[i];
}

void append(char s[], char n)
{
    int len = strlen(s);
    s[len] = n;
    s[len + 1] = '\0';
}

double pow(double base, double exponent)
{
    if (exponent == 0)
    {
        return 1;
    }

    double result = base;
    int i;

    for (i = 1; i < exponent; i++)
    {
        result *= base;
    }

    return result;
}

void E9_print(char *string)
{
    while (*string)
    {
        outb(0xE9, *string);
        string++;
    }
}