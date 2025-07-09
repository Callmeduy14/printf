#include "ft_printf_bonus.h"

int print_ptr(t_flag *flag, va_list args)
{
	unsigned long n = (unsigned long)va_arg(args, void *);
	int len = ft_numlen(n, 16);
	int num_len = (n == 0 && flag->dot && flag->precision == 0) ? 0 : len;
	int prefix = 2;
	int pad = flag->width - num_len - prefix;
	int count = 0;
	if (!flag->minus && (!flag->zero || flag->dot))
		while (pad-- > 0)
			count += ft_putchar(' ');
	count += ft_putstr("0x", -1);
	if (!flag->minus && flag->zero && !flag->dot)
		while (pad-- > 0)
			count += ft_putchar('0');
	if (!(n == 0 && flag->dot && flag->precision == 0))
		count += ft_puthex(n, 0, 0, flag->zero && !flag->dot, num_len);
	if (flag->minus)
		while (pad-- > 0)
			count += ft_putchar(' ');
	return count;
} 