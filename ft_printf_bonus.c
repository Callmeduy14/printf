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


static int print_char(char c, int *count)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	(*count)++;
	return (0);
}

static int process_format(const char **fmt, va_list args, int *count)
{
	t_format	f;
	int		 chars_printed;

	f = ft_parse_format(fmt, args);
	chars_printed = ft_handle_format(args, f);
	if (chars_printed == -1)
		return (-1);
	*count += chars_printed;
	return (0);
}


int ft_printf_bonus(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	if (!format)
		return (-1);

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (process_format(&format, args, &count) == -1)
				break ;
		}
		else if (print_char(*format++, &count) == -1)
			break ;
	}
	va_end(args);
	return (count);
}
