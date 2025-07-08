#ifndef FT_PRINTF_BONUS_H
#define FT_PRINTF_BONUS_H

#include <stdarg.h>
#include <unistd.h>

// Struct untuk menyimpan hasil parsing format
typedef struct s_fmt {
    int flag_minus;
    int flag_zero;
    int flag_hash;
    int flag_plus;
    int flag_space;
    int width;
    int precision;
    int precision_specified;
    char specifier;
} t_fmt;

// Fungsi utama versi bonus
int ft_printf(const char *format, ...);

#endif // FT_PRINTF_BONUS_H 