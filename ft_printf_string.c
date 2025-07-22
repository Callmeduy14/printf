/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:32:29 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 17:32:01 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Fungsi untuk menangani string NULL, mengembalikan string pengganti jika NULL
static char	*handle_null_string(char *str, const char *nullstr)
{
	if (!str) // Jika pointer string NULL
		return ((char *)nullstr); // Kembalikan string pengganti
	return (str); // Jika tidak NULL, kembalikan string asli
}

// Menghitung jumlah spasi padding yang dibutuhkan berdasarkan lebar dan panjang string yang akan dicetak
static int	calculate_padding(t_format fmt, int print_len)
{
	int	pad_space;

	pad_space = fmt.width - print_len; // Hitung sisa lebar
	if (pad_space < 0)
		pad_space = 0; // Tidak boleh negatif
	return (pad_space); // Return jumlah spasi
}

// Mengisi buffer dengan string dan padding sesuai format (left/right align)
static void	fill_buffer(char *buffer, t_format fmt, char *str, int print_len)
{
	int	pos;       // Posisi buffer
	int	pad_space; // Jumlah padding spasi

	pos = 0; // Inisialisasi posisi buffer
	pad_space = calculate_padding(fmt, print_len); // Hitung padding
	// Jika right align (tanpa minus), isi padding di depan
	if (!fmt.minus && pad_space > 0)
	{
		while (pos < pad_space)
		{
			buffer[pos] = ' '; // Isi spasi di depan
			pos++;
		}
	}
	// Salin string ke buffer
	ft_memcpy(buffer + pos, str, print_len); // Salin string ke buffer
	pos += print_len; // Geser posisi
	// Jika left align (minus), isi padding di belakang
	if (fmt.minus && pad_space > 0)
	{
		while (pos < fmt.width)
		{
			buffer[pos] = ' '; // Isi spasi di belakang
			pos++;
		}
	}
}

// Fungsi utama untuk mencetak string dengan format
int	ft_print_string(t_format fmt, char *str)
{
	char		buffer[1024];    // Buffer hasil akhir
	const char	*nullstr;      // String pengganti jika NULL
	int		print_len;      // Panjang string yang akan dicetak
	int		total_len;      // Total karakter yang dicetak
	char		*processed_str; // String yang sudah diproses (NULL diganti)

	nullstr = "(null)"; // String pengganti jika NULL
	processed_str = handle_null_string(str, nullstr); // Proses NULL
	print_len = ft_strlen(processed_str); // Hitung panjang string
	// Jika ada flag precision, batasi panjang string
	if (fmt.dot == 1 && fmt.precision >= 0 && fmt.precision < print_len)
		print_len = fmt.precision; // Batasi panjang sesuai precision
	fill_buffer(buffer, fmt, processed_str, print_len); // Isi buffer
	total_len = calculate_padding(fmt, print_len) + print_len; // Total karakter
	// Tulis hasil ke stdout
	if (write(1, buffer, total_len) == -1)
		return (-1);
	return (total_len); // Return jumlah karakter yang dicetak
}
