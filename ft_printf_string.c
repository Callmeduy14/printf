/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:32:29 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 11:14:13 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(t_format fmt, char *str)
{
	char	buffer[1024]; // Buffer cukup besar untuk string panjang
	int	pos;	   // Posisi penulisan dalam buffer
	const char	*nullstr = "(null)";
	int	print_len;	 // Panjang string yang akan dicetak
	int	pad_space;	 // Jumlah padding yang dibutuhkan

	pos = 0;
	// Handle string NULL
	if (!str)
		str = (char *)nullstr;

	// Hitung panjang string
	print_len = ft_strlen(str);

	// Apply precision jika ada
	if (fmt.dot == 1 && fmt.precision >= 0 && fmt.precision < print_len)
		print_len = fmt.precision;

	// Hitung padding space
	pad_space = fmt.width - print_len;
	if (pad_space < 0)
		pad_space = 0;

	// Right alignment (padding sebelum string)
	if (!fmt.minus && pad_space > 0)
	{
		// Isi buffer dengan spasi
		while (pos < pad_space)
		{
			buffer[pos] = ' ';
			pos++;
		}
	}

	// Salin string ke buffer
	ft_memcpy(buffer + pos, str, print_len);
	pos += print_len;

	// Left alignment (padding setelah string)
	if (fmt.minus && pad_space > 0)
	{
		// Isi buffer dengan spasi
		while (pos < fmt.width)
		{
			buffer[pos] = ' ';
			pos++;
		}
	}

	// Tulis seluruh buffer sekaligus
	if (write(1, buffer, pos) == -1)
		return (-1);

	return (pos);
}

