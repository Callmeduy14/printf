/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:18:22 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 21:40:44 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_format_specifier(const char **format, va_list args, int *count)
{
	int			temp;
	t_format	fmt;

	if (*(*format + 1) == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		(*count)++;
		*format += 2;
		return (0);
	}
	(*format)++;
	fmt = ft_parse_format(format, args);
	temp = ft_handle_format(args, fmt);
	if (temp == -1)
		return (-1);
	*count += temp;
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (handle_format_specifier(&format, args, &count) == -1)
				return (-1);
		}
		else
		{
			if (write(1, format, 1) == -1)
				return (-1);
			count++;
			format++;
		}
	}
	va_end(args);
	return (count);
}

int	ft_handle_format(va_list args, t_format fmt)
{
	if (fmt.type == 'c')
		return (ft_print_char(fmt, va_arg(args, int)));
	else if (fmt.type == 's')
		return (ft_print_string(fmt, va_arg(args, char *)));
	else if (fmt.type == 'p')
		return (ft_print_pointer(fmt, va_arg(args, unsigned long)));
	else if (fmt.type == 'd' || fmt.type == 'i')
		return (ft_print_int(fmt, va_arg(args, int)));
	else if (fmt.type == 'u')
		return (ft_print_unsigned(fmt, va_arg(args, unsigned int)));
	else if (fmt.type == 'x')
		return (ft_print_hex(fmt, va_arg(args, unsigned int)));
	else if (fmt.type == 'X')
		return (ft_print_hex(fmt, va_arg(args, unsigned int)));
	else if (fmt.type == '%')
		return (ft_print_percent(fmt));
	else
		return (0);
}
