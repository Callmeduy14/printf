/* ************************************************************************** */
/*                                                                            */
/*   File: ft_padding.c                                                        */
/*   Berisi fungsi untuk menghitung dan menulis padding (spasi/nol)            */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Menulis karakter padding ke buffer integer
void	handle_padding_int(int count, char c, char *buf, int *pos)
{
	while (count-- > 0)
		buf[(*pos)++] = c;
}

// Menulis karakter padding ke buffer unsigned
void	handle_padding_unsign(char *buffer, int *pos, int pad, char c)
{
	while (pad-- > 0)
		buffer[(*pos)++] = c;
}

// Hitung padding untuk unsigned integer (nol dan spasi)
int	calculate_unsigned_padding(t_format fmt, int len,
	unsigned int n, int *paddings)
{
	int	total;

	paddings[0] = 0; // padding nol
	paddings[1] = 0; // padding spasi
	if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
		len = 0;
	if (fmt.dot == 1 && fmt.precision > len)
		paddings[0] = fmt.precision - len;
	total = paddings[0] + len;
	if (len == 0)
		total = 0;
	if (fmt.width > total)
		paddings[1] = fmt.width - total;
	return (total);
}

// Hitung padding untuk hex (spasi) dengan memperhitungkan prefix
int	calculate_hex_padding(t_format *fmt, t_intvars *v, unsigned int n)
{
	int	total_len;

	total_len = 0;
	if (fmt->hash && n != 0)
		total_len += 2; // prefix '0x' atau '0X'
	total_len += v->pad_zero + v->len;
	v->pad_space = 0;
	if (fmt->width > total_len)
		v->pad_space = fmt->width - total_len;
	return (v->pad_space);
}

// Hitung padding spasi untuk string
int	calculate_string_padding(t_format fmt, int print_len)
{
	int	pad_space;

	pad_space = fmt.width - print_len;
	if (pad_space < 0)
		pad_space = 0;
	return (pad_space);
}
