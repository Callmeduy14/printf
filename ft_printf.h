#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>

int ft_printf(const char *format, ...);

static int ft_putchar(char c);
static int ft_putstr(const char *s);

static int ft_putnbr(int n);
static int ft_putunbr(unsigned int n);
static int ft_puthex(unsigned long n, int upper);
static int ft_putptr(void *ptr);

int ft_printf_bonus(const char *format, ...);

#endif // FT_PRINTF_H
