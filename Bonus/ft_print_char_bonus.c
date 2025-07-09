#include "ft_printf_bonus.h"

int print_char(t_flag *flag, va_list args)
{
	char c = (char)va_arg(args, int);
	int count = 0;
	int pad = flag->width > 1 ? flag->width - 1 : 0;
	if (!flag->minus)
		while (pad-- > 0)
			count += ft_putchar(flag->zero ? '0' : ' ');
	count += ft_putchar(c);
	if (flag->minus)
		while (++pad < flag->width - 1)
			count += ft_putchar(' ');
	return count;
} 