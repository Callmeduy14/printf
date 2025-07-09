#include "ft_printf_bonus.h"

static int dispatch_print(t_flag *flag, va_list args)
{
	if (flag->type == 'c')
		return print_char(flag, args);
	if (flag->type == 's')
		return print_str(flag, args);
	if (flag->type == 'p')
		return print_ptr(flag, args);
	if (flag->type == 'd' || flag->type == 'i')
		return print_nbr(flag, args);
	if (flag->type == 'u')
		return print_unsigned(flag, args);
	if (flag->type == 'x')
		return print_hex(flag, args, 0);
	if (flag->type == 'X')
		return print_hex(flag, args, 1);
	if (flag->type == '%')
		return print_percent(flag);
	return 0;
}

int ft_printf(const char *format, ...)
{
	va_list args;
	int i = 0;
	int count = 0;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			t_flag flag = {0};
			i++;
			parse_flags(format, &i, &flag, args);
			count += dispatch_print(&flag, args);
		}
		else
		{
			count += ft_putchar(format[i]);
			i++;
		}
	}
	va_end(args);
	return count;
} 