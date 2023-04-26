#include <stddef.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#define cli asm("cli" ::)
#define sti asm("sti" ::)

void *memcpy(char *dst, char *src, int n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char value);
unsigned short inw(unsigned short port);
void outw(unsigned short port, unsigned short value);
void delay(uint32_t ms);
void itoa(char *buf, unsigned long int n, int base);
int strlen(char s[]);
int strcmp(char s1[], char s2[]);
void append(char s[], char n);
double pow(double base, double exponent);
void E9_print(char *string);