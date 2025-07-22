/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 20:58:22 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Menghitung jumlah padding nol dan spasi yang dibutuhkan untuk unsigned integer
static int	calculate_paddings(t_format fmt, int len, unsigned int n, int *paddings)
{
	int	total;

	// Jika precision 0 dan nilai 0, tidak ada digit yang dicetak
	if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
		len = 0;
	// Hitung padding nol jika precision lebih besar dari digit
	if (fmt.dot == 1 && fmt.precision > len)
		paddings[0] = fmt.precision - len;
	total = paddings[0] + len; // Total digit + padding nol
	if (len == 0)
		total = 0;
	// Hitung padding spasi jika width lebih besar dari total digit+zero
	if (fmt.width > total)
		paddings[1] = fmt.width - total;
	return (total);
}

// Mengisi buffer dengan karakter padding (spasi/0)
static void	handle_padding(char *buffer, int *pos, int pad, char c)
{
	while (pad > 0)
	{
		buffer[(*pos)++] = c; // Isi buffer dengan karakter padding
		pad--;
	}
}

// Menentukan karakter padding utama (spasi/0) sesuai flag
static char	get_pad_char(t_format fmt)
{
	char	pad_char;

	pad_char = ' '; // Default spasi
	if (fmt.zero && fmt.dot == 0)
		pad_char = '0'; // Jika flag zero aktif dan tidak ada precision, pakai '0'
	return (pad_char);
}

// Menyalin digit angka ke buffer, kecuali jika harus di-skip (precision 0 dan n=0)
static void	handle_number(char *buffer, int *pos, char *num, t_format fmt)
{
	int	i;

	i = 0;
	if (!(fmt.dot == 1 && fmt.precision == 0 && ft_atoi(num) == 0)) // Jika bukan kasus skip
	{
		while (num[i])
		{
			buffer[(*pos)++] = num[i]; // Salin digit ke buffer
			i++;
		}
	}
}

// Fungsi utama untuk mencetak unsigned integer dengan format
int	ft_print_unsigned(t_format fmt, unsigned int n)
{
	char	buffer[256]; // Buffer hasil akhir
	int		pos;         // Posisi buffer
	char	*num;        // String hasil konversi
	int		paddings[2]; // [0]=zero, [1]=space
	int		total;       // Total digit yang dicetak
	char	pad_char;    // Karakter padding

	pos = 0;            // Inisialisasi posisi buffer
	paddings[0] = 0;    // Padding nol
	paddings[1] = 0;    // Padding spasi
	num = ft_utoa(n);   // Konversi unsigned ke string
	if (!num)
		return (-1);      // Jika gagal alokasi
	total = calculate_paddings(fmt, ft_strlen(num), n, paddings); // Hitung padding
	pad_char = get_pad_char(fmt); // Tentukan karakter padding
	// Padding spasi di depan jika right align
	if (!fmt.minus && paddings[1] > 0)
		handle_padding(buffer, &pos, paddings[1], pad_char);
	// Padding nol di depan digit
	handle_padding(buffer, &pos, paddings[0], '0');
	// Salin digit angka
	handle_number(buffer, &pos, num, fmt);
	// Padding spasi di belakang jika left align
	if (fmt.minus && paddings[1] > 0)
		handle_padding(buffer, &pos, paddings[1], ' ');
	free(num); // Bebaskan memori
	// Tulis hasil ke stdout
	if (write(1, buffer, pos) == -1)
		return (-1);
	return (pos); // Return jumlah karakter yang dicetak
}
