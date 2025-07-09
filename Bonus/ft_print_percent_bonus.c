#include "ft_printf_bonus.h"

int print_percent(t_flag *flag)
{
	int count = 0;
	int pad = flag->width > 1 ? flag->width - 1 : 0;
	if (!flag->minus)
		while (pad-- > 0)
			count += ft_putchar(flag->zero ? '0' : ' ');
	count += ft_putchar('%');
	if (flag->minus)
		while (++pad < flag->width - 1)
			count += ft_putchar(' ');
	return count;
} 