#include "ft_printf_bonus.h"

int print_unsigned(t_flag *flag, va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	int len = ft_numlen(n, 10);
	int num_len = (n == 0 && flag->dot && flag->precision == 0) ? 0 : len;
	int pad = flag->width - num_len;
	int count = 0;
	if (!flag->minus && (!flag->zero || flag->dot))
		while (pad-- > 0)
			count += ft_putchar(' ');
	if (!flag->minus && flag->zero && !flag->dot)
		while (pad-- > 0)
			count += ft_putchar('0');
	if (!(n == 0 && flag->dot && flag->precision == 0))
		count += ft_putnbr(n, num_len, 0, flag->zero && !flag->dot);
	if (flag->minus)
		while (pad-- > 0)
			count += ft_putchar(' ');
	return count;
} 