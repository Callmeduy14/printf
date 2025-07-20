/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:44:49 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/20 13:44:50 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

// Fungsi utama ft_printf_bonus: versi bonus dari ft_printf yang mendukung flag tambahan
// format: string format seperti printf biasa
// ...: argumen variadik
// Return: jumlah karakter yang dicetak, atau -1 jika error
int ft_printf_bonus(const char *format, ...)
{
	va_list	 args;   // Menyimpan argumen variadik
	int		 count;  // Total karakter yang dicetak
	int		 temp;   // Menyimpan hasil cetak per format
	t_format	fmt;	// Struktur untuk menyimpan parsing format

	// Jika format NULL, return error
	if (format == NULL)
		return (-1);
	va_start(args, format); // Inisialisasi argumen variadik
	count = 0;
	while (*format != '\0') // Iterasi setiap karakter format
	{
		if (*format == '%') // Jika menemukan '%', berarti ada format spesial
		{
			format++;
			// Parsing flag, width, precision, dsb ke struct fmt
			fmt = ft_parse_format(&format, args);
			// Handle konversi dan cetak sesuai format, simpan jumlah karakter
			temp = ft_handle_format(args, fmt);
			if (temp == -1)
			{
				va_end(args); // Error: tutup argumen variadik
				return (-1);
			}
			count += temp; // Tambah jumlah karakter yang dicetak
		}
		else
		{
			// Jika bukan '%', cetak karakter biasa
			if (write(1, format, 1) == -1)
			{
				va_end(args);
				return (-1);
			}
			count++;
			format++;
		}
	}
	va_end(args); // Tutup argumen variadik
	return (count); // Return total karakter yang dicetak
}
