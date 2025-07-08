#include "ft_printf.h"

// Menulis satu karakter ke stdout
// Return: jumlah karakter yang ditulis (selalu 1)
int ft_putchar(char c) {
    return write(1, &c, 1);
}

// Menulis string ke stdout, jika NULL akan menulis (null)
// Return: jumlah karakter yang ditulis
int ft_putstr(const char *s) {
    int len = 0;
    if (!s)
        s = "(null)";
    while (*s) {
        len += ft_putchar(*s++);
    }
    return len;
}

// Menulis integer bertanda (signed) ke stdout
// Return: jumlah karakter yang ditulis
int ft_putnbr(int n) {
    int len = 0;
    if (n == -2147483648) // Penanganan khusus untuk batas bawah int
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

// Menulis unsigned integer ke stdout
// Return: jumlah karakter yang ditulis
int ft_putunbr(unsigned int n) {
    int len = 0;
    if (n >= 10)
        len += ft_putunbr(n / 10);
    len += ft_putchar((n % 10) + '0');
    return len;
}

// Menulis angka dalam format heksadesimal
// uppercase: 0 = huruf kecil, 1 = huruf besar
// Return: jumlah karakter yang ditulis
int ft_puthex(unsigned long n, int uppercase) {
    int len = 0;
    char *base = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    if (n >= 16)
        len += ft_puthex(n / 16, uppercase);
    len += ft_putchar(base[n % 16]);
    return len;
}

/*
 * Fungsi utama ft_printf
 * Mirip dengan printf asli, membaca format string dan mengganti setiap format spesifier
 * dengan argumen yang sesuai. Mendukung: %c, %s, %d, %i, %u, %x, %X, %p, dan %%
 * Return: jumlah karakter yang ditulis
 */
int ft_printf(const char *format, ...) {
    va_list args;
    int i = 0, len = 0;

    va_start(args, format);
    while (format[i]) {
        if (format[i] == '%' && format[i + 1]) {
            i++;
            if (format[i] == 'c') // karakter
                len += ft_putchar(va_arg(args, int));
            else if (format[i] == 's') // string
                len += ft_putstr(va_arg(args, char *));
            else if (format[i] == 'd' || format[i] == 'i') // integer
                len += ft_putnbr(va_arg(args, int));
            else if (format[i] == 'u') // unsigned integer
                len += ft_putunbr(va_arg(args, unsigned int));
            else if (format[i] == 'x') // hex lowercase
                len += ft_puthex(va_arg(args, unsigned int), 0);
            else if (format[i] == 'X') // hex uppercase
                len += ft_puthex(va_arg(args, unsigned int), 1);
            else if (format[i] == 'p') { // pointer
                len += ft_putstr("0x");
                len += ft_puthex((unsigned long)va_arg(args, void *), 0);
            }
            else // jika spesifier tidak dikenali, tulis apa adanya
                len += ft_putchar(format[i]);
        } else {
            len += ft_putchar(format[i]);
        }
        i++;
    }
    va_end(args);
    return len;
} 