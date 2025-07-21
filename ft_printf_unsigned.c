/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 11:21:17 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(t_format fmt, unsigned int n)
{
	char buffer[256];  // Buffer cukup untuk unsigned int terbesar
	int pos;	   // Posisi penulisan dalam buffer
	char *num;		 // String hasil konversi
	int len;	   // Panjang digit
	int pad_zero;  // Jumlah zero padding
	int pad_space; // Jumlah space padding
	int i;
	char	pad_char;
	int total;

	pos = 0;
	len = 0;
	pad_zero = 0;
	pad_space = 0;
	// Konversi angka ke string
	num = ft_utoa(n);
	if (!num)
		return (-1);

	// Hitung panjang digit
	i = 0;
	while (num[i])
		i++;
	len = i;

	// Handle kasus precision 0 dan angka 0
	if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
		len = 0;

	// Hitung zero padding dari precision
	if (fmt.dot == 1 && fmt.precision > len)
		pad_zero = fmt.precision - len;

	// Hitung total panjang output
	total = pad_zero + len;
	if (len == 0)
		total = 0;

	// Hitung space padding dari width
	if (fmt.width > total)
		pad_space = fmt.width - total;

	// Tentukan karakter padding
	pad_char = ' ';
	if (fmt.zero && fmt.dot == 0)
		pad_char = '0';

	// Right alignment (padding sebelum konten)
	if (!fmt.minus && pad_space > 0)
	{
		// Isi buffer dengan padding karakter
		while (pad_space > 0)
		{
			buffer[pos++] = pad_char;
			pad_space--;
		}
	}

	// Isi zero padding dari precision
	while (pad_zero > 0)
	{
		buffer[pos++] = '0';
		pad_zero--;
	}

	// Cetak digit (kecuali precision=0 dan n=0)
	if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0))
	{
		// Salin digit ke buffer
		i = 0;
		while (num[i])
		{
			buffer[pos++] = num[i];
			i++;
		}
	}

	// Left alignment (padding setelah konten)
	if (fmt.minus && pad_space > 0)
	{
		// Isi buffer dengan spasi
		while (pad_space > 0)
		{
			buffer[pos++] = ' ';
			pad_space--;
		}
	}

	free(num);

	// Tulis seluruh buffer sekaligus
	if (write(1, buffer, pos) == -1)
		return -1;

	return (pos);
}
