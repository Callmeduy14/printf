#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

// Structure to hold formatting options for each conversion
typedef struct s_format
{
	int flag_minus;    // '-' flag: left-justify
	int flag_zero;     // '0' flag: zero-padding
	int flag_hash;     // '#' flag: alternate form
	int flag_space;    // ' ' flag: space before positive numbers
	int flag_plus;     // '+' flag: always show sign
	int width;         // Minimum field width
	int precision;     // Precision (after '.')
	int precision_specified; // 1 if precision is specified, 0 otherwise
	char specifier;    // Conversion specifier (c, s, d, etc.)
}   t_format;

// Main printf function
int	ft_printf(const char *format, ...);

// Parsing function for format options
int	parse_format(const char *format, int i, t_format *fmt, va_list args);

// Handler functions for each specifier, now take t_format *
int	ft_handle_char(va_list args, t_format *fmt);
int	ft_handle_string(va_list args, t_format *fmt);
int	ft_handle_pointer(va_list args, t_format *fmt);
int	ft_handle_decimal(va_list args, t_format *fmt);
int	ft_handle_integer(va_list args, t_format *fmt);
int	ft_handle_unsigned(va_list args, t_format *fmt);
int	ft_handle_hex_lower(va_list args, t_format *fmt);
int	ft_handle_hex_upper(va_list args, t_format *fmt);
int	ft_handle_percent(t_format *fmt);

// Utility functions
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int n);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_putnbr_hex(unsigned long n, int uppercase);
int	ft_putnbr_hex_pointer(unsigned long n);
int	ft_strlen(char *str);
void	ft_putchar_fd(char c, int fd);

// New utility functions for bonus features
int	ft_print_padding(char c, int count);
int	ft_putstr_len(char *str, int len);
int	ft_putnbr_positive(int n);
int	ft_count_digits(int n);
int	ft_count_digits_unsigned(unsigned int n);
int	ft_count_digits_hex(unsigned long n);
int	ft_handle_int_min(t_format *fmt);

#endif // FT_PRINTF_H 