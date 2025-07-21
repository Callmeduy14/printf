/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 11:02:27 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(t_format fmt, unsigned int n, int uppercase)
{
	char buffer[256];  // Buffer cukup untuk hex panjang
	int pos = 0;	   // Posisi penulisan dalam buffer
	char *hex;		 // String hasil konversi hex
	int prefix = 0;	// Flag prefix "0x"/"0X"
	int pad_zero = 0;  // Jumlah zero padding
	int pad_space = 0; // Jumlah space padding
	int len = 0;	   // Panjang digit hex
	char pad_char;	 // Karakter padding (' ' atau '0')

	// Konversi angka ke string hex
	hex = ft_xtoa(n, uppercase);
	if (!hex)
		return -1;

	// Hitung panjang digit hex
	len = ft_strlen(hex);

	// Handle kasus precision 0 dan angka 0
	if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
		len = 0;

	// Hitung zero padding dari precision
	if (fmt.dot == 1 && fmt.precision > len)
		pad_zero = fmt.precision - len;

	// Tentukan perlu prefix "0x" atau "0X"
	if (fmt.hash && n != 0)
		prefix = 2;

	// Hitung total panjang output
	int total_len = prefix + pad_zero + len;

	// Hitung space padding dari width
	if (fmt.width > total_len)
		pad_space = fmt.width - total_len;

	// Tentukan karakter padding
	pad_char = ' ';
	if (fmt.zero && !fmt.minus && !fmt.dot)
		pad_char = '0';

	// Right alignment (padding sebelum konten)
	if (!fmt.minus)
	{
		// Jika padding dengan '0', cetak prefix dulu
		if (pad_char == '0' && prefix)
		{
			buffer[pos++] = '0';
			if (uppercase)
				buffer[pos++] = 'X';
			else
				buffer[pos++] = 'x';
			prefix = 0;
		}

		// Isi padding space/zero
		while (pad_space > 0)
		{
			buffer[pos++] = pad_char;
			pad_space--;
		}
	}

	// Cetak prefix jika belum dicetak
	if (prefix)
	{
		buffer[pos++] = '0';
		if (uppercase)
			buffer[pos++] = 'X';
		else
			buffer[pos++] = 'x';
	}

	// Isi zero padding dari precision
	while (pad_zero > 0)
	{
		buffer[pos++] = '0';
		pad_zero--;
	}

	// Cetak digit hex (kecuali precision=0 dan n=0)
	if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0))
	{
		// Salin digit hex ke buffer
		int i = 0;
		while (hex[i])
		{
			buffer[pos++] = hex[i];
			i++;
		}
	}

	// Left alignment (padding setelah konten)
	if (fmt.minus)
	{
		while (pad_space > 0)
		{
			buffer[pos++] = ' ';
			pad_space--;
		}
	}

	free(hex);

	// Tulis seluruh buffer sekaligus
	if (write(1, buffer, pos) == -1)
		return (-1);

	return (pos);
}

