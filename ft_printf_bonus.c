#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int ft_putchar(char c) { return write(1, &c, 1); }

static int ft_putnchar(char c, int n) {
    int count = 0;
    while (n > 0) {
        count += ft_putchar(c);
        n--;
    }
    return count;
}

static int ft_strlen(const char *s) {
    int len = 0;
    if (!s) return 6; // (null)
    while (s[len]) len++;
    return len;
}

static int ft_putstr_prec(const char *s, int prec) {
    int len = 0;
    if (!s) s = "(null)";
    while (s[len] && (prec < 0 || len < prec)) {
        ft_putchar(s[len]);
        len++;
    }
    return len;
}

static int ft_putnbr(int n) {
    int count = 0;
    char c;
    if (n == -2147483648)
        return write(1, "-2147483648", 11);
    if (n < 0) {
        count += ft_putchar('-');
        n = -n;
    }
    if (n > 9)
        count += ft_putnbr(n / 10);
    c = n % 10 + '0';
    count += ft_putchar(c);
    return count;
}

static int ft_nbrlen(int n) {
    int len = (n <= 0) ? 1 : 0;
    while (n) {
        n /= 10;
        len++;
    }
    return len;
}

static int print_d(int n, int width, int minus, int zero, int prec, int dot, int plus, int space) {
    int count = 0;
    int len = ft_nbrlen(n);
    int neg = (n < 0);
    int pad_zero = 0;
    int pad_space = 0;
    int sign = 0;
    if (dot && prec == 0 && n == 0) len = 0;
    if (prec > len - neg) pad_zero = prec - (len - neg);
    // sign: 1 if need to print + or space
    if (!neg && plus)
        sign = 1;
    else if (!neg && space)
        sign = 2;
    if (width > len + pad_zero + (sign ? 1 : 0))
        pad_space = width - (len + pad_zero + (sign ? 1 : 0));
    if (!minus) count += ft_putnchar(zero && !dot ? '0' : ' ', pad_space);
    if (neg) count += ft_putchar('-');
    else if (sign == 1) count += ft_putchar('+');
    else if (sign == 2) count += ft_putchar(' ');
    count += ft_putnchar('0', pad_zero);
    if (!(dot && prec == 0 && n == 0)) count += ft_putnbr(neg ? -n : n);
    if (minus) count += ft_putnchar(' ', pad_space);
    return count;
}

static int print_s(const char *s, int width, int minus, int prec, int dot) {
    int count = 0;
    int len = ft_strlen(s);
    if (dot && prec < len) len = prec;
    if (!minus && width > len) count += ft_putnchar(' ', width - len);
    count += ft_putstr_prec(s, len);
    if (minus && width > len) count += ft_putnchar(' ', width - len);
    return count;
}

static int ft_puthex_bonus(unsigned int n, int upper) {
    int count = 0;
    char *base;
    base = upper ? "0123456789ABCDEF" : "0123456789abcdef";
    if (n >= 16)
        count += ft_puthex_bonus(n / 16, upper);
    count += ft_putchar(base[n % 16]);
    return count;
}

static int print_x(unsigned int n, int width, int minus, int zero, int prec, int dot, int hash, int upper) {
    int count = 0;
    int len = 1;
    unsigned int tmp = n;
    int pad_zero = 0;
    int pad_space = 0;
    int prefix = 0;
    while ((tmp /= 16)) len++;
    if (dot && prec == 0 && n == 0) len = 0;
    if (prec > len) pad_zero = prec - len;
    if (hash && n != 0) prefix = 2;
    if (width > len + pad_zero + prefix)
        pad_space = width - (len + pad_zero + prefix);
    if (!minus) count += ft_putnchar(zero && !dot ? '0' : ' ', pad_space);
    if (prefix) {
        if (upper) count += ft_putstr_prec("0X", 2);
        else count += ft_putstr_prec("0x", 2);
    }
    count += ft_putnchar('0', pad_zero);
    if (!(dot && prec == 0 && n == 0)) count += ft_puthex_bonus(n, upper);
    if (minus) count += ft_putnchar(' ', pad_space);
    return count;
}

static int parse_flags(const char *f, int *i, int *minus, int *zero, int *width, int *dot, int *prec, int *plus, int *space, int *hash, va_list args) {
    while (f[*i] == '-' || f[*i] == '0' || f[*i] == '+' || f[*i] == ' ' || f[*i] == '#') {
        if (f[*i] == '-') *minus = 1;
        if (f[*i] == '0') *zero = 1;
        if (f[*i] == '+') *plus = 1;
        if (f[*i] == ' ') *space = 1;
        if (f[*i] == '#') *hash = 1;
        (*i)++;
    }
    if (f[*i] >= '0' && f[*i] <= '9') {
        *width = 0;
        while (f[*i] >= '0' && f[*i] <= '9') {
            *width = *width * 10 + (f[*i] - '0');
            (*i)++;
        }
    }
    if (f[*i] == '.') {
        *dot = 1;
        (*i)++;
        *prec = 0;
        while (f[*i] >= '0' && f[*i] <= '9') {
            *prec = *prec * 10 + (f[*i] - '0');
            (*i)++;
        }
    }
    return 0;
}

int ft_printf_bonus(const char *format, ...) {
    va_list args;
    int i = 0, count = 0;
    va_start(args, format);
    while (format[i]) {
        if (format[i] == '%') {
            int minus = 0, zero = 0, width = 0, dot = 0, prec = -1;
            int plus = 0, space = 0, hash = 0;
            i++;
            parse_flags(format, &i, &minus, &zero, &width, &dot, &prec, &plus, &space, &hash, args);
            if (format[i] == 'd' || format[i] == 'i')
                count += print_d(va_arg(args, int), width, minus, zero, prec, dot, plus, (plus ? 0 : space));
            else if (format[i] == 's')
                count += print_s(va_arg(args, char *), width, minus, prec, dot);
            else if (format[i] == 'x')
                count += print_x(va_arg(args, unsigned int), width, minus, zero, prec, dot, hash, 0);
            else if (format[i] == 'X')
                count += print_x(va_arg(args, unsigned int), width, minus, zero, prec, dot, hash, 1);
            else if (format[i] == '%')
                count += ft_putchar('%');
        } else {
            count += ft_putchar(format[i]);
        }
        i++;
    }
    va_end(args);
    return count;
} 