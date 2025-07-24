/* ************************************************************************** */
/*                                                                            */
/*   File: ft_printf_hex.c                                                     */
/*   Berisi fungsi untuk mencetak angka dalam format hexadecimal               */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Menulis prefix '0x' atau '0X' jika flag hash aktif dan n != 0
static void	write_prefix(t_format *fmt, t_intvars *v, char *buffer,
			unsigned int n)
{
	if (fmt->hash && n != 0)
	{
		buffer[v->pos++] = '0';
		if (fmt->type == 'X')
			buffer[v->pos++] = 'X';
		else
			buffer[v->pos++] = 'x';
	}
}

// Menulis isi utama hex ke buffer, termasuk padding nol
static void	write_content(t_intvars *v, char *hex, char *buffer, t_format *fmt)
{
	while (v->pad_zero-- > 0)
		buffer[v->pos++] = '0';
	if (!(fmt->dot && fmt->precision == 0 && hex[0] == '0'))
	{
		while (*hex)
			buffer[v->pos++] = *hex++;
	}
}

// Menulis seluruh output hex ke buffer sesuai format
int	write_hex_to_buffer(t_format *fmt, t_intvars *v,
		char *buffer, unsigned int n)
{
	char	*hex;

	hex = v->hex;
	// Jika padding dengan '0', prefix ditulis sebelum padding
	if (!fmt->minus && v->pad_char == '0')
		write_prefix(fmt, v, buffer, n);
	if (!fmt->minus)
	{
		while (v->pad_space-- > 0)
			buffer[v->pos++] = v->pad_char;
	}
	// Jika bukan padding '0', prefix ditulis setelah padding
	if (!(!fmt->minus && v->pad_char == '0'))
		write_prefix(fmt, v, buffer, n);
	write_content(v, hex, buffer, fmt); // Tulis isi utama
	if (fmt->minus)
	{
		while (v->pad_space-- > 0)
			buffer[v->pos++] = ' ';
	}
	return (v->pos);
}

// Alokasi buffer dan tulis output hex, lalu cetak ke stdout
static int	alloc_and_write_hex(t_format *fmt, t_intvars *v,
			char *hex, unsigned int n)
{
	size_t	buffer_size;
	char	*buffer;
	int		len;

	buffer_size = v->pad_space + v->pad_zero + ft_strlen(hex) + 4; // Estimasi
	buffer = malloc(buffer_size);
	if (!buffer)
		return (-1);
	v->hex = hex;
	len = write_hex_to_buffer(fmt, v, buffer, n); // Bangun string output
	if (write(1, buffer, len) == -1)
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	return (len);
}

// Fungsi utama untuk mencetak unsigned integer dalam format hex
int	ft_print_hex(t_format fmt, unsigned int n)
{
	char		*hex;
	t_intvars	v;
	int			len;

	v.pos = 0;
	init_hex_vars(&fmt, n, &v, &hex); // Inisialisasi variabel bantu
	if (!hex)
		return (-1);
	calculate_hex_padding(&fmt, &v, n); // Hitung padding
	len = alloc_and_write_hex(&fmt, &v, hex, n); // Bangun dan cetak output
	free(hex);
	return (len);
}
