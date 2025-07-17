#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <unistd.h>    // Untuk write()
# include <stdarg.h>    // Untuk va_list
# include <stdlib.h>    // Untuk malloc() dan free()

// Struktur untuk menyimpan informasi format
typedef struct s_format
{
    int     minus;      // Flag '-'
    int     zero;       // Flag '0'
    int     width;      // Minimum width
    int     precision;  // Precision
    int     dot;        // Flag '.' (ada precision)
    int     hash;       // Flag '#'
    int     space;      // Flag ' ' (spasi)
    int     plus;       // Flag '+'
    char    type;       // Tipe konversi (c, s, p, d, i, u, x, X, %)
}           t_format;

// Prototipe fungsi utama
int         ft_printf(const char *format, ...);

// Fungsi parser dan handler
t_format    ft_parse_format(const char **format, va_list args);
int         ft_handle_format(const char **format, va_list args, t_format fmt);

// Fungsi pencetakan dengan format
int         ft_print_char(t_format fmt, int c);
int         ft_print_string(t_format fmt, char *str);
int         ft_print_pointer(t_format fmt, unsigned long ptr);
int         ft_print_int(t_format fmt, int n);
int         ft_print_unsigned(t_format fmt, unsigned int n);
int         ft_print_hex(t_format fmt, unsigned int n, int uppercase);
int         ft_print_percent(t_format fmt);

// Fungsi utilitas
size_t      ft_strlen(const char *s);
void        ft_putchar_fd(char c, int fd);
void        ft_putstr_fd(char *s, int fd);
int         ft_putnchar_fd(char c, int n, int fd);
int         ft_isdigit(int c);
char        *ft_itoa(int n);
char        *ft_utoa(unsigned int n);
char        *ft_xtoa(unsigned long n, int uppercase);

#endif