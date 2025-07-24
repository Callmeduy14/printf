/* ************************************************************************** */
/*                                                                            */
/*   File: ft_printf_unsigned.c                                                */
/*   Berisi fungsi untuk mencetak unsigned integer dengan format printf        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Mendapatkan karakter padding ('0' jika flag zero dan tidak ada precision)
char	get_pad_char(t_format fmt)
{
	char	pad_char;

	pad_char = ' ';
	if (fmt.zero && !fmt.dot)
		pad_char = '0';
	return (pad_char);
}

// Menyalin angka ke buffer jika bukan edge case zero-precision
void	handle_number(char *buffer, int *pos, char *num, t_format fmt)
{
	int	i;

	i = 0;
	if (!(fmt.dot && fmt.precision == 0 && ft_atoi(num) == 0))
	{
		while (num[i])
			buffer[(*pos)++] = num[i++];
	}
}

// Hitung total panjang output (termasuk padding)
static int	calculate_total_length(t_format fmt, int num_len, unsigned int n)
{
	int	total;

	total = num_len;
	if (fmt.precision > num_len)
		total = fmt.precision;
	if (fmt.width > total)
		total = fmt.width;
	if (fmt.dot && fmt.precision == 0 && n == 0)
		total = fmt.width;
	return (total);
}

// Bangun string output unsigned integer ke buffer sesuai format
static void	build_unsigned_str(char *str, t_format fmt,
			char *num, int paddings[2])
{
	int		pos;
	char	pad_char;

	pos = 0;
	pad_char = get_pad_char(fmt);
	if (!fmt.minus && paddings[1] > 0)
		handle_padding_unsign(str, &pos, paddings[1], pad_char); // Padding kiri
	handle_padding_unsign(str, &pos, paddings[0], '0'); // Padding nol
	handle_number(str, &pos, num, fmt); // Tulis angka utama
	if (fmt.minus && paddings[1] > 0)
		handle_padding_unsign(str, &pos, paddings[1], ' '); // Padding kanan
}

// Fungsi utama untuk mencetak unsigned integer
int	ft_print_unsigned(t_format fmt, unsigned int n)
{
	char	*num;
	char	*output;
	int		paddings[2];
	int		total_len;
	int		result;

	num = ft_utoa(n); // Konversi ke string
	if (!num)
		return (-1);
	calculate_unsigned_padding(fmt, ft_strlen(num), n, paddings); // Hitung padding
	total_len = calculate_total_length(fmt, ft_strlen(num), n); // Total panjang output
	output = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!output)
	{
		free(num);
		return (-1);
	}
	build_unsigned_str(output, fmt, num, paddings); // Bangun string output
	free(num);
	result = write(1, output, total_len); // Cetak ke stdout
	free(output);
	if (result == -1)
		return (-1);
	return (total_len);
}
