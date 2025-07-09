#include "ft_printf_bonus.h"

int print_str(t_flag *flag, va_list args)
{
	char *s = va_arg(args, char *);
	int len = ft_strlen(s);
	int print_len = len;
	int count = 0;
	if (flag->dot && flag->precision < print_len)
		print_len = flag->precision;
	int pad = flag->width > print_len ? flag->width - print_len : 0;
	if (!flag->minus)
		while (pad-- > 0)
			count += ft_putchar(flag->zero ? '0' : ' ');
	count += ft_putstr(s, print_len);
	if (flag->minus)
		while (++pad < flag->width - print_len)
			count += ft_putchar(' ');
	return count;
} 