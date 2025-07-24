/* ************************************************************************** */
/*                                                                            */
/*   File: ft_printf_bonus.c                                                   */
/*   Berisi implementasi bonus flag untuk ft_printf (flag tambahan)            */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

// Cetak satu karakter dan update count
static int	print_char(char c, int *count)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	(*count)++;
	return (0);
}

// Proses format setelah '%' untuk bonus flag
static int	process_format(const char **fmt, va_list args, int *count)
{
	t_format	f;
	int			chars_printed;

	f = ft_parse_format(fmt, args); // Parsing format
	chars_printed = ft_handle_format(args, f); // Cetak sesuai tipe
	if (chars_printed == -1)
		return (-1);
	*count += chars_printed;
	return (0);
}

// Fungsi utama ft_printf_bonus: mirip ft_printf, tapi support flag bonus
int	ft_printf_bonus(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (process_format(&format, args, &count) == -1)
				break ;
		}
		else if (print_char(*format++, &count) == -1)
			break ;
	}
	va_end(args);
	return (count);
}
