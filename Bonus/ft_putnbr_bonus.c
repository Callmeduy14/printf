#include "ft_printf_bonus.h"

int ft_putnbr(long n, int len, int sign, int pad_zero)
{
	char buf[20];
	int i = 0, count = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n > 0)
	{
		buf[i++] = '0' + (n % 10);
		n /= 10;
	}
	while (i < len)
		buf[i++] = pad_zero ? '0' : ' ';
	while (i-- > 0)
		count += ft_putchar(buf[i]);
	return count;
}

int ft_puthex(unsigned long n, int upper, int prefix, int pad_zero, int len)
{
	char buf[20];
	char *base = upper ? "0123456789ABCDEF" : "0123456789abcdef";
	int i = 0, count = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n > 0)
	{
		buf[i++] = base[n % 16];
		n /= 16;
	}
	while (i < len)
		buf[i++] = pad_zero ? '0' : ' ';
	while (i-- > 0)
		count += ft_putchar(buf[i]);
	return count;
} 