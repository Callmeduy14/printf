/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:44:22 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 11:00:31 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Inisialisasi struct format dengan nilai default
** Semua flag di-set ke 0, precision ke -1, type ke 0
*/
static t_format	ft_init_format(void)
{
	t_format	fmt;
	fmt.minus = 0;
	fmt.zero = 0;
	fmt.width = 0;
	fmt.precision = -1;
	fmt.dot = 0;
	fmt.hash = 0;
	fmt.space = 0;
	fmt.plus = 0;
	fmt.type = 0;
	return (fmt);
}
/*
** Mengurai flags (-, 0, #, +, spasi) dari format string
** Mengupdate struct fmt sesuai flag yang ditemukan
*/
static void ft_parse_flags(const char **format, t_format *fmt)
{
	// Loop selama karakter adalah flag
	while (**format == '-' || **format == '0' || **format == '#' ||
			**format == '+' || **format == ' ')
	{
		if (**format == '-')
			fmt->minus = 1;
		else if (**format == '0')
			fmt->zero = 1;
		else if (**format == '#')
			fmt->hash = 1;
		else if (**format == '+')
			fmt->plus = 1;
		else if (**format == ' ')
			fmt->space = 1;
		(*format)++; // Geser pointer ke karakter berikutnya
	}
}
/*
** Mengurai width (angka atau *) dari format string
** Jika width berupa '*', ambil dari argumen variadic
*/
static void	ft_parse_width(const char **format, t_format *fmt, va_list args)
{
	if (**format == '*')
	{
		fmt->width = va_arg(args, int);
		if (fmt->width < 0)
		{
			fmt->minus = 1;
			fmt->width = -fmt->width;
		}
		(*format)++;
	}
	else
	{
		fmt->width = 0;
		while (ft_isdigit(**format))
		{
			fmt->width = fmt->width * 10 + (**format - '0');
			(*format)++;
		}
	}
}
/*
** Mengurai precision (.angka atau .*) dari format string
** Jika precision berupa '*', ambil dari argumen variadic
*/
static void	ft_parse_precision(const char **format, t_format *fmt, va_list args)
{
	if (**format == '.')
	{
		(*format)++;
		fmt->dot = 1;
		fmt->precision = 0;
		if (**format == '*')
		{
			fmt->precision = va_arg(args, int);
			(*format)++;
		}
		else
		{
			while (ft_isdigit(**format))
			{
				fmt->precision = fmt->precision * 10 + (**format - '0');
				(*format)++;
			}
		}
	}
}

/*
** Fungsi utama untuk mengurai format
** Mengembalikan struct t_format hasil parsing flag, width, precision, dan type
*/
t_format	ft_parse_format(const char **format, va_list args)
{
	t_format	fmt;
	fmt = ft_init_format(); // Set default
	ft_parse_flags(format, &fmt); // Parse flag
	ft_parse_width(format, &fmt, args); // Parse width
	ft_parse_precision(format, &fmt, args); // Parse precision
	fmt.type = **format; // Ambil type (c, s, d, i, u, x, X, p, %)
	(*format)++;
	return (fmt);
}
