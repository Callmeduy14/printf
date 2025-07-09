#include "ft_printf_bonus.h"

int ft_putchar(char c)
{
	return write(1, &c, 1);
}

int ft_putstr(char *s, int max)
{
	int i = 0;
	if (!s)
		s = "(null)";
	while (s[i] && (max < 0 || i < max))
		i++;
	write(1, s, i);
	return i;
}

int ft_strlen(const char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return i;
}

int ft_numlen(long n, int base)
{
	int len = (n <= 0);
	while (n)
	{
		n /= base;
		len++;
	}
	return len;
} 