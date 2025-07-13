#include "ft_printf.h"

// Main ft_printf implementation with bonus support and comments
int ft_printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	int i = 0;

	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			t_format fmt = {0};
			// Parse format options (flags, width, precision, specifier)
			i = parse_format(format, i + 1, &fmt, args);
			// Call the appropriate handler based on the specifier
			switch (fmt.specifier)
			{
				case 'c': count += ft_handle_char(args, &fmt); break;
				case 's': count += ft_handle_string(args, &fmt); break;
				case 'p': count += ft_handle_pointer(args, &fmt); break;
				case 'd': count += ft_handle_decimal(args, &fmt); break;
				case 'i': count += ft_handle_integer(args, &fmt); break;
				case 'u': count += ft_handle_unsigned(args, &fmt); break;
				case 'x': count += ft_handle_hex_lower(args, &fmt); break;
				case 'X': count += ft_handle_hex_upper(args, &fmt); break;
				case '%': count += ft_handle_percent(&fmt); break;
				default:  count += ft_putchar(fmt.specifier); break;
			}
		}
		else
		{
			// Print normal characters
			count += ft_putchar(format[i]);
		}
		i++;
	}
	va_end(args);
	return (count);
}

// Parse format options (flags, width, precision, specifier) from format string
// Returns the index of the specifier character
int parse_format(const char *format, int i, t_format *fmt, va_list args)
{
	// Reset format struct
	fmt->flag_minus = 0;
	fmt->flag_zero = 0;
	fmt->flag_hash = 0;
	fmt->flag_space = 0;
	fmt->flag_plus = 0;
	fmt->width = 0;
	fmt->precision = 0;
	fmt->precision_specified = 0;
	fmt->specifier = 0;

	// Parse flags
	while (format[i] == '-' || format[i] == '0' || format[i] == '#' || format[i] == ' ' || format[i] == '+')
	{
		if (format[i] == '-') fmt->flag_minus = 1;
		if (format[i] == '0') fmt->flag_zero = 1;
		if (format[i] == '#') fmt->flag_hash = 1;
		if (format[i] == ' ') fmt->flag_space = 1;
		if (format[i] == '+') fmt->flag_plus = 1;
		i++;
	}
	// Parse width
	if (format[i] == '*')
	{
		fmt->width = va_arg(args, int);
		i++;
	}
	else
	{
		while (format[i] >= '0' && format[i] <= '9')
		{
			fmt->width = fmt->width * 10 + (format[i] - '0');
			i++;
		}
	}
	// Parse precision
	if (format[i] == '.')
	{
		fmt->precision_specified = 1;
		fmt->precision = 0;
		i++;
		if (format[i] == '*')
		{
			fmt->precision = va_arg(args, int);
			i++;
		}
		else
		{
			while (format[i] >= '0' && format[i] <= '9')
			{
				fmt->precision = fmt->precision * 10 + (format[i] - '0');
				i++;
			}
		}
	}
	// Set the specifier
	fmt->specifier = format[i];
	return i;
} 