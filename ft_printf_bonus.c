/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:44:49 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 14:16:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

// Mencetak satu karakter ke stdout dan menambah counter
static int print_char(char c, int *count)
{
	if (write(1, &c, 1) == -1) // Tulis karakter ke layar, jika gagal return -1
		return (-1);
	(*count)++; // Tambah jumlah karakter yang dicetak
	return (0);
}

// Memproses format spesifier setelah '%', parsing dan handle format
static int process_format(const char **fmt, va_list args, int *count)
{
	t_format	f; // Struktur format
	int		 chars_printed; // Jumlah karakter yang dicetak

	f = ft_parse_format(fmt, args); // Parse format spesifier
	chars_printed = ft_handle_format(args, f); // Cetak sesuai format
	if (chars_printed == -1)
		return (-1);
	*count += chars_printed; // Tambah jumlah karakter total
	return (0);
}

// Fungsi utama printf versi bonus, mendukung flag tambahan
int ft_printf_bonus(const char *format, ...)
{
	va_list	args; // Variadic argument list
	int		count; // Jumlah karakter yang dicetak

	count = 0; // Inisialisasi counter
	if (!format)
		return (-1); // Jika format NULL, return error

	va_start(args, format); // Mulai membaca argumen variadic
	while (*format) // Selama masih ada karakter di format string
	{
		if (*format == '%') // Jika menemukan '%', berarti ada format spesifier
		{
			format++; // Geser ke karakter berikutnya
			if (process_format(&format, args, &count) == -1) // Proses format
				break ; // Jika error, keluar loop
		}
		else if (print_char(*format++, &count) == -1) // Jika bukan '%', cetak karakter biasa
			break ; // Jika error, keluar loop
	}
	va_end(args); // Selesai membaca argumen variadic
	return (count); // Return jumlah karakter yang dicetak
}
