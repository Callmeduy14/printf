/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:43:45 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 11:07:10 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

int ft_print_int(t_format fmt, int n)
{
	char buffer[256];  // Buffer cukup untuk angka panjang
	int pos = 0;	   // Posisi penulisan dalam buffer
	char *num;		 // String hasil konversi angka
	int is_neg = 0;	// Flag angka negatif
	int print_sign = 0;// Flag perlu tanda +/spasi
	int pad_zero = 0;  // Jumlah zero padding
	int pad_space = 0; // Jumlah space padding
	int len = 0;	   // Panjang digit
	char pad_char;	 // Karakter padding (' ' atau '0')

	// Konversi angka ke string
	num = ft_itoa(n);
	if (!num)
		return -1;

	// Tentukan flag negatif
	if (n < 0)
		is_neg = 1;

	// Hitung panjang digit (abaikan tanda minus)
	len = ft_strlen(num);
	if (is_neg)
		len--;

	// Handle kasus precision 0 dan angka 0
	if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
		len = 0;

	// Hitung zero padding dari precision
	if (fmt.dot == 1 && fmt.precision > len)
		pad_zero = fmt.precision - len;

	// Tentukan apakah perlu tanda + atau spasi
	if (is_neg || fmt.plus || fmt.space)
		print_sign = 1;

	// Hitung total panjang output
	int total_len = print_sign + pad_zero + len;

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
		// Jika padding dengan '0', cetak tanda dulu
		if (pad_char == '0' && print_sign)
		{
			if (is_neg)
				buffer[pos++] = '-';
			else if (fmt.plus)
				buffer[pos++] = '+';
			else if (fmt.space)
				buffer[pos++] = ' ';
			print_sign = 0;
		}
		// Isi padding space/zero
		while (pad_space > 0)
		{
			buffer[pos++] = pad_char;
			pad_space--;
		}
	}
	// Cetak tanda jika belum dicetak
	if (print_sign)
	{
		if (is_neg)
			buffer[pos++] = '-';
		else if (fmt.plus)
			buffer[pos++] = '+';
		else if (fmt.space)
			buffer[pos++] = ' ';
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
		// Lewati tanda '-' jika ada
		char *digits = num;
		if (is_neg)
			digits++;

		// Salin digit ke buffer
		while (*digits)
		{
			buffer[pos++] = *digits;
			digits++;
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
	free(num);
	// Tulis seluruh buffer sekaligus
	if (write(1, buffer, pos) == -1)
		return (-1);

	return (pos);
}

