/* ************************************************************************** */
/*                                                                            */
/*   File: ft_conversion_utils.c                                               */
/*   Berisi fungsi utilitas konversi angka ke string (unsigned, hex)           */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Hitung jumlah digit unsigned integer
static int	ft_unsigned_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

// Konversi unsigned integer ke string
char	*ft_utoa(unsigned int n)
{
	char	*str;
	int		len;
	int		i;

	len = ft_unsigned_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = len - 1;
	if (n == 0)
		str[i] = '0';
	while (n != 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}

// Hitung jumlah digit angka dalam basis 16 (hex)
static int	ft_hex_len(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

// Konversi unsigned long ke string hex (huruf besar/kecil sesuai argumen)
char	*ft_xtoa(unsigned long n, int uppercase)
{
	char	*str;
	int		len;
	int		i;
	char	*hex_chars;

	if (uppercase)
		hex_chars = "0123456789ABCDEF";
	else
		hex_chars = "0123456789abcdef";
	len = ft_hex_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	i = len - 1;
	while (n != 0)
	{
		str[i] = hex_chars[n % 16];
		n /= 16;
		i--;
	}
	return (str);
}
