/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:29:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 14:02:59 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Mengisi buffer dengan karakter padding (spasi) sesuai kebutuhan
static void	fill_padding(char *buffer, int *pos, int padding, char pad_char)
{
	while (*pos < padding) // Selama posisi saat ini kurang dari jumlah padding
	{
		buffer[*pos] = pad_char; // Isi buffer dengan karakter padding
		(*pos)++; // Geser posisi ke kanan
	}
}

// Fungsi utama untuk mencetak karakter dengan format (width, align)
int	ft_print_char(t_format fmt, int c)
{
	char	buffer[256]; // Buffer untuk menampung hasil akhir sebelum ditulis
	int		pos;         // Posisi saat ini di buffer
	int		padding;     // Jumlah padding yang dibutuhkan

	pos = 0;             // Inisialisasi posisi buffer ke 0
	padding = 0;         // Inisialisasi padding ke 0
	// Hitung padding jika width > 1
	if (fmt.width > 1)
		padding = fmt.width - 1; // Padding = width - 1 karakter yang akan dicetak

	// Padding di depan jika right align
	if (!fmt.minus && padding > 0)
		fill_padding(buffer, &pos, padding, ' '); // Isi spasi di depan karakter

	// Masukkan karakter ke buffer
	buffer[pos] = (char)c; // Simpan karakter yang akan dicetak
	pos++;                // Geser posisi buffer

	// Padding di belakang jika left align
	if (fmt.minus && padding > 0)
		fill_padding(buffer, &pos, fmt.width, ' '); // Isi spasi di belakang karakter

	// Tulis hasil ke stdout
	if (write(1, buffer, pos) == -1) // Tulis buffer ke layar, jika gagal return -1
		return (-1);
	return (pos); // Return jumlah karakter yang dicetak
}
