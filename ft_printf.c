#include "ft_printf.h"

static int ft_putchar(char c)
{
    return write(1, &c, 1);
}

static int ft_putstr(const char *s)
{
    int len = 0;
    if (!s)
        s = "(null)";
    while (s[len])
        ft_putchar(s[len++]);
    return len;
}

static int ft_putnbr(int n)
{
    int count = 0;
    char c;
    if (n == -2147483648)
        return write(1, "-2147483648", 11);
    if (n < 0)
    {
        count += ft_putchar('-');
        n = -n;
    }
    if (n > 9)
        count += ft_putnbr(n / 10);
    c = n % 10 + '0';
    count += ft_putchar(c);
    return count;
}

static int ft_putunbr(unsigned int n)
{
    int count = 0;
    char c;
    if (n > 9)
        count += ft_putunbr(n / 10);
    c = n % 10 + '0';
    count += ft_putchar(c);
    return count;
}

static int ft_puthex(unsigned long n, int upper)
{
    int count = 0;
    char *base;
    base = upper ? "0123456789ABCDEF" : "0123456789abcdef";
    if (n >= 16)
        count += ft_puthex(n / 16, upper);
    count += ft_putchar(base[n % 16]);
    return count;
}

static int ft_putptr(void *ptr)
{
    int count = 0;
    unsigned long addr = (unsigned long)ptr;
    count += ft_putstr("0x");
    count += ft_puthex(addr, 0);
    return count;
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int i = 0;
    int count = 0;

    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'c')
                count += ft_putchar(va_arg(args, int));
            else if (format[i] == 's')
                count += ft_putstr(va_arg(args, char *));
            else if (format[i] == 'd' || format[i] == 'i')
                count += ft_putnbr(va_arg(args, int));
            else if (format[i] == 'u')
                count += ft_putunbr(va_arg(args, unsigned int));
            else if (format[i] == 'x')
                count += ft_puthex(va_arg(args, unsigned int), 0);
            else if (format[i] == 'X')
                count += ft_puthex(va_arg(args, unsigned int), 1);
            else if (format[i] == 'p')
                count += ft_putptr(va_arg(args, void *));
            else if (format[i] == '%')
                count += ft_putchar('%');
        }
        else
            count += ft_putchar(format[i]);
        i++;
    }
    va_end(args);
    return count;
} 