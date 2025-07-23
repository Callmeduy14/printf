/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:32:29 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 20:32:56 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*handle_null_string(char *str, const char *nullstr)
{
	if (!str)
		return ((char *)nullstr);
	return (str);
}

static void	fill_buffer(char *buffer, t_format fmt, char *str, int print_len)
{
	int	pos;
	int	pad_space;

	pos = 0;
	pad_space = calculate_string_padding(fmt, print_len);
	if (!fmt.minus && pad_space > 0)
	{
		while (pos < pad_space)
		{
			buffer[pos] = ' ';
			pos++;
		}
	}
	ft_memcpy(buffer + pos, str, print_len);
	pos += print_len;
	if (fmt.minus && pad_space > 0)
	{
		while (pos < fmt.width)
		{
			buffer[pos] = ' ';
			pos++;
		}
	}
}

int	ft_print_string(t_format fmt, char *str)
{
	char		buffer[1024];
	const char	*nullstr;
	int			print_len;
	int			total_len;
	char		*processed_str;

	nullstr = "(null)";
	processed_str = handle_null_string(str, nullstr);
	print_len = ft_strlen(processed_str);
	if (fmt.dot == 1 && fmt.precision >= 0 && fmt.precision < print_len)
		print_len = fmt.precision;
	fill_buffer(buffer, fmt, processed_str, print_len);
	total_len = calculate_string_padding(fmt, print_len) + print_len;
	if (write(1, buffer, total_len) == -1)
		return (-1);
	return (total_len);
}
