#include "ft_printf_bonus.h"

// Fungsi untuk inisialisasi struct format
t_fmt fmt_init(void) {
    t_fmt fmt;
    fmt.flag_minus = 0;
    fmt.flag_zero = 0;
    fmt.flag_hash = 0;
    fmt.flag_plus = 0;
    fmt.flag_space = 0;
    fmt.width = 0;
    fmt.precision = 0;
    fmt.precision_specified = 0;
    fmt.specifier = 0;
    return fmt;
}

// Fungsi parser: mengisi struct format dari format string, mulai dari index *i
// Return: index setelah specifier
int parse_format(const char *s, int i, t_fmt *fmt, va_list args) {
    // Parsing flag
    while (s[i] == '-' || s[i] == '0' || s[i] == '#' || s[i] == '+' || s[i] == ' ') {
        if (s[i] == '-') fmt->flag_minus = 1;
        if (s[i] == '0') fmt->flag_zero = 1;
        if (s[i] == '#') fmt->flag_hash = 1;
        if (s[i] == '+') fmt->flag_plus = 1;
        if (s[i] == ' ') fmt->flag_space = 1;
        i++;
    }
    // Parsing width
    while (s[i] >= '0' && s[i] <= '9') {
        fmt->width = fmt->width * 10 + (s[i] - '0');
        i++;
    }
    // Parsing precision
    if (s[i] == '.') {
        fmt->precision_specified = 1;
        i++;
        fmt->precision = 0;
        while (s[i] >= '0' && s[i] <= '9') {
            fmt->precision = fmt->precision * 10 + (s[i] - '0');
            i++;
        }
    }
    // Parsing specifier
    if (s[i] == 'c' || s[i] == 's' || s[i] == 'p' || s[i] == 'd' || s[i] == 'i' ||
        s[i] == 'u' || s[i] == 'x' || s[i] == 'X' || s[i] == '%') {
        fmt->specifier = s[i];
        i++;
    }
    return i;
} 