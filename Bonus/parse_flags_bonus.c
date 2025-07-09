#include "ft_printf_bonus.h"

static int is_flag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '#' || c == ' ' || c == '+');
}

int parse_flags(const char *format, int *i, t_flag *flag, va_list args)
{
	while (is_flag(format[*i]))
	{
		if (format[*i] == '-')
			flag->minus = 1;
		else if (format[*i] == '0')
			flag->zero = 1;
		else if (format[*i] == '#')
			flag->hash = 1;
		else if (format[*i] == ' ')
			flag->space = 1;
		else if (format[*i] == '+')
			flag->plus = 1;
		else if (format[*i] == '.')
		{
			flag->dot = 1;
			(*i)++;
			flag->precision = 0;
			while (format[*i] >= '0' && format[*i] <= '9')
				flag->precision = flag->precision * 10 + (format[(*i)++] - '0');
			continue;
		}
		(*i)++;
	}
	if (format[*i] >= '0' && format[*i] <= '9')
	{
		flag->width = 0;
		while (format[*i] >= '0' && format[*i] <= '9')
			flag->width = flag->width * 10 + (format[(*i)++] - '0');
	}
	flag->type = format[*i];
	(*i)++;
	return 0;
} 