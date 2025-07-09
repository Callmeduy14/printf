#include "ft_printf_bonus.h"

static int print_sign(long n, t_flag *flag)
{
	if (n < 0)
		return ft_putchar('-');
	if (flag->plus)
		return ft_putchar('+');
	if (flag->space)
		return ft_putchar(' ');
	return 0;
}

int print_nbr(t_flag *flag, va_list args)
{
	long n = va_arg(args, int);
	int len = ft_numlen(n, 10);
	int sign = (n < 0 || flag->plus || flag->space);
	int num_len = (n == 0 && flag->dot && flag->precision == 0) ? 0 : len;
	int pad = flag->width - num_len - (sign ? 1 : 0);
	int count = 0;
	if (!flag->minus && (!flag->zero || flag->dot))
		while (pad-- > 0)
			count += ft_putchar(' ');
	count += print_sign(n, flag);
	if (!flag->minus && flag->zero && !flag->dot)
		while (pad-- > 0)
			count += ft_putchar('0');
	if (!(n == 0 && flag->dot && flag->precision == 0))
		count += ft_putnbr(n < 0 ? -n : n, num_len, 0, flag->zero && !flag->dot);
	if (flag->minus)
		while (pad-- > 0)
			count += ft_putchar(' ');
	return count;
} 