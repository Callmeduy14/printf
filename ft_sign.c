/* ************************************************************************** */
/*                                                                            */
/*   File: ft_sign.c                                                          */
/*   Berisi fungsi untuk menangani tanda (+, -, spasi) dan cetak '%'          */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Cetak satu karakter ke stdout
int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

// Cetak karakter '%' dengan padding sesuai format
int	ft_print_percent(t_format fmt)
{
	int	count;
	int	padding;

	count = 0;
	padding = fmt.width - 1;
	// Padding kiri dengan '0' jika flag zero
	if (fmt.zero && !fmt.minus && padding > 0)
	{
		while (padding-- > 0)
			count += ft_putchar('0');
	}
	// Padding kiri dengan spasi jika tidak ada flag zero
	else if (!fmt.minus && padding > 0)
	{
		while (padding-- > 0)
			count += ft_putchar(' ');
	}
	count += ft_putchar('%'); // Cetak karakter '%'
	// Padding kanan jika flag minus
	if (fmt.minus && padding > 0)
	{
		while (padding-- > 0)
			count += ft_putchar(' ');
	}
	return (count);
}

// Menulis tanda (+, -, spasi) ke buffer integer jika diperlukan
void	handle_sign_int(int n, t_format fmt, char *buf, int *pos)
{
	if (n < 0)
		buf[(*pos)++] = '-';
	else if (fmt.plus)
		buf[(*pos)++] = '+';
	else if (fmt.space)
		buf[(*pos)++] = ' ';
}
