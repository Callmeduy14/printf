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

static void	ft_parse_flags(const char **format, t_format *fmt)
{
	while (**format == '-' || **format == '0' || **format == '#'
		|| **format == '+' || **format == ' ')
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
		(*format)++;
	}
}

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

t_format	ft_parse_format(const char **format, va_list args)
{
	t_format	fmt;

	fmt = ft_init_format();
	ft_parse_flags(format, &fmt);
	ft_parse_width(format, &fmt, args);
	ft_parse_precision(format, &fmt, args);
	fmt.type = **format;
	(*format)++;
	return (fmt);
}
