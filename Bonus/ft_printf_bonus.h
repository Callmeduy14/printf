#ifndef FT_PRINTF_BONUS_H
#define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

// Struktur untuk menyimpan flag dan field width/precision
typedef struct s_flag {
	int minus;
	int zero;
	int width;
	int dot;
	int precision;
	int hash;
	int space;
	int plus;
	char type;
} t_flag;

int ft_printf(const char *format, ...);

// Fungsi parsing flag dan konversi
int parse_flags(const char *format, int *i, t_flag *flag, va_list args);

// Fungsi print per tipe
int print_char(t_flag *flag, va_list args);
int print_str(t_flag *flag, va_list args);
int print_ptr(t_flag *flag, va_list args);
int print_nbr(t_flag *flag, va_list args);
int print_unsigned(t_flag *flag, va_list args);
int print_hex(t_flag *flag, va_list args, int upper);
int print_percent(t_flag *flag);

// Fungsi utilitas
int ft_putchar(char c);
int ft_putstr(char *s, int max);
int ft_putnbr(long n, int len, int sign, int pad_zero);
int ft_puthex(unsigned long n, int upper, int prefix, int pad_zero, int len);
int ft_numlen(long n, int base);
int ft_strlen(const char *s);

#endif 