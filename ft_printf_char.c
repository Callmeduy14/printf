/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:29:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 11:01:52 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_print_char(t_format fmt, int c)
{
	char	buffer[256];  // Buffer cukup untuk menampung karakter + padding
	int	pos = 0;	   // Posisi penulisan dalam buffer
	int	padding = 0;   // Jumlah padding yang dibutuhkan
	char	ch = (char)c; // Konversi ke char

	// Hitung jumlah padding jika width > 1
	if (fmt.width > 1)
		padding = fmt.width - 1;

	// Right alignment (padding sebelum karakter)
	if (!fmt.minus && padding > 0)
	{
		// Isi buffer dengan spasi untuk padding
		while (pos < padding)
		{
			buffer[pos] = ' ';
			pos++;
		}
	}

	// Tambahkan karakter utama ke buffer
	buffer[pos] = ch;
	pos++;

	// Left alignment (padding setelah karakter)
	if (fmt.minus && padding > 0)
	{
		// Isi buffer dengan spasi untuk padding
		while (pos < fmt.width)
		{
			buffer[pos] = ' ';
			pos++;
		}
	}

	// Tulis seluruh buffer sekaligus
	if (write(1, buffer, pos) == -1)
		return -1;

	return (pos);
}
