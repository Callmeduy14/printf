#include "ft_printf.h"

// Print satu karakter
static int ft_putchar(char c) {
    return write(1, &c, 1);
}

// Print string, handle NULL
static int ft_putstr(const char *s) {
    int len = 0;
    if (!s)
        s = "(null)";
    while (*s)
        len += ft_putchar(*s++);
    return len;
}

// Print integer signed
static int ft_putnbr(int n) {
    int len = 0;
    if (n == -2147483648)
        return ft_putstr("-2147483648");
    if (n < 0) {
        len += ft_putchar('-');
        n = -n;
    }
    if (n >= 10)
        len += ft_putnbr(n / 10);
    len += ft_putchar((n % 10) + '0');
    return len;
}

// Print unsigned integer
static int ft_putunbr(unsigned int n) {
    int len = 0;
    if (n >= 10)
        len += ft_putunbr(n / 10);
    len += ft_putchar((n % 10) + '0');
    return len;
}

// Print heksadesimal
static int ft_puthex(unsigned long n, int upper) {
    int len = 0;
    char *base = upper ? "0123456789ABCDEF" : "0123456789abcdef";
    if (n >= 16)
        len += ft_puthex(n / 16, upper);
    len += ft_putchar(base[n % 16]);
    return len;
}

// Fungsi utama
int ft_printf(const char *format, ...) {
    va_list args;
    int i = 0, len = 0;

    va_start(args, format);
    while (format[i]) {
        if (format[i] == '%' && format[i + 1]) {
            i++;
            if (format[i] == 'c')
                len += ft_putchar(va_arg(args, int));
            else if (format[i] == 's')
                len += ft_putstr(va_arg(args, char *));
            else if (format[i] == 'd' || format[i] == 'i')
                len += ft_putnbr(va_arg(args, int));
            else if (format[i] == 'u')
                len += ft_putunbr(va_arg(args, unsigned int));
            else if (format[i] == 'x')
                len += ft_puthex(va_arg(args, unsigned int), 0);
            else if (format[i] == 'X')
                len += ft_puthex(va_arg(args, unsigned int), 1);
            else if (format[i] == 'p') {
                len += ft_putstr("0x");
                len += ft_puthex((unsigned long)va_arg(args, void *), 0);
            }
            else if (format[i] == '%')
                len += ft_putchar('%');
            else
                len += ft_putchar(format[i]);
        } else {
            len += ft_putchar(format[i]);
        }
        i++;
    }
    va_end(args);
    return len;
} 