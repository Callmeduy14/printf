#include "ft_printf_bonus.h"

static int print_prefix(t_flag *flag, unsigned int n, int upper)
{
	if (flag->hash && n != 0)
	{
		if (upper)
			return ft_putstr("0X", -1);
		else
			return ft_putstr("0x", -1);
	}
	return 0;
}

int print_hex(t_flag *flag, va_list args, int upper)
{
	unsigned int n = va_arg(args, unsigned int);
	int len = ft_numlen(n, 16);
	int num_len = (n == 0 && flag->dot && flag->precision == 0) ? 0 : len;
	int prefix = (flag->hash && n != 0) ? 2 : 0;
	int pad = flag->width - num_len - prefix;
	int count = 0;
	if (!flag->minus && (!flag->zero || flag->dot))
		while (pad-- > 0)
			count += ft_putchar(' ');
	count += print_prefix(flag, n, upper);
	if (!flag->minus && flag->zero && !flag->dot)
		while (pad-- > 0)
			count += ft_putchar('0');
	if (!(n == 0 && flag->dot && flag->precision == 0))
		count += ft_puthex(n, upper, 0, flag->zero && !flag->dot, num_len);
	if (flag->minus)
		while (pad-- > 0)
			count += ft_putchar(' ');
	return count;
} 