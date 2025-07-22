/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:44:22 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 14:12:06 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Inisialisasi struktur format dengan nilai default
static t_format	ft_init_format(void)
{
	t_format	fmt;

	fmt.minus = 0;      // Flag '-'
	fmt.zero = 0;       // Flag '0'
	fmt.width = 0;      // Lebar minimum
	fmt.precision = -1; // Precision default -1 (tidak ada)
	fmt.dot = 0;        // Flag '.'
	fmt.hash = 0;       // Flag '#'
	fmt.space = 0;      // Flag ' '
	fmt.plus = 0;       // Flag '+'
	fmt.type = 0;       // Tipe konversi
	return (fmt);
}

// Parsing flag-flag format (misal: '-', '0', '#', '+', ' ')
static void	ft_parse_flags(const char **format, t_format *fmt)
{
	while (**format == '-' || **format == '0' || **format == '#'
		|| **format == '+' || **format == ' ')
	{
		if (**format == '-')
			fmt->minus = 1; // Flag minus
		else if (**format == '0')
			fmt->zero = 1; // Flag zero
		else if (**format == '#')
			fmt->hash = 1; // Flag hash
		else if (**format == '+')
			fmt->plus = 1; // Flag plus
		else if (**format == ' ')
			fmt->space = 1; // Flag spasi
		(*format)++; // Geser ke karakter berikutnya
	}
}

// Parsing width (lebar minimum)
static void	ft_parse_width(const char **format, t_format *fmt, va_list args)
{
	if (**format == '*') // Jika width pakai '*'
	{
		fmt->width = va_arg(args, int); // Ambil dari argumen
		if (fmt->width < 0)
		{
			fmt->minus = 1; // Jika negatif, aktifkan minus
			fmt->width = -fmt->width;
		}
		(*format)++;
	}
	else
	{
		fmt->width = 0;
		while (ft_isdigit(**format)) // Jika digit, parsing manual
		{
			fmt->width = fmt->width * 10 + (**format - '0');
			(*format)++;
		}
	}
}

// Parsing precision (setelah titik)
static void	ft_parse_precision(const char **format, t_format *fmt, va_list args)
{
	if (**format == '.')
	{
		(*format)++;
		fmt->dot = 1; // Aktifkan flag dot
		fmt->precision = 0;
		if (**format == '*') // Precision pakai '*'
		{
			fmt->precision = va_arg(args, int);
			(*format)++;
		}
		else
		{
			while (ft_isdigit(**format)) // Parsing digit precision
			{
				fmt->precision = fmt->precision * 10 + (**format - '0');
				(*format)++;
			}
		}
	}
}

// Fungsi utama parsing format spesifier
// Mengisi struktur t_format dari string format
// Menggeser pointer format ke karakter setelah spesifier
// Contoh: "%10.5d" -> width=10, precision=5, type='d'
t_format	ft_parse_format(const char **format, va_list args)
{
	t_format	fmt;

	fmt = ft_init_format(); // Inisialisasi default
	ft_parse_flags(format, &fmt); // Parsing flag
	ft_parse_width(format, &fmt, args); // Parsing width
	ft_parse_precision(format, &fmt, args); // Parsing precision
	fmt.type = **format; // Ambil tipe konversi
	(*format)++; // Geser pointer format
	return (fmt); // Return struktur format
}
