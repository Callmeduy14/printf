/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:32:29 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 22:19:14 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*handle_null_string(char *str, const char *nullstr)
{
	if (!str)
		return ((char *)nullstr);
	return (str);
}

static int	write_string_part(const char *str, int len)
{
	int		written;
	int		ret;

	written = 0;
	while (written < len)
	{
		ret = write(1, str + written, len - written);
		if (ret == -1)
			return (-1);
		written += ret;
	}
	return (written);
}

static int	write_padded_string(t_format fmt, char *str, int print_len)
{
	int	total_len;
	int	pad_space;
	int	written;

	total_len = 0;
	pad_space = calculate_string_padding(fmt, print_len);
	if (!fmt.minus && pad_space > 0)
	{
		written = write_padding(pad_space, ' ');
		if (written == -1)
			return (-1);
		total_len += written;
	}
	written = write_string_part(str, print_len);
	if (written == -1)
		return (-1);
	total_len += written;
	if (fmt.minus && pad_space > 0)
	{
		written = write_padding(pad_space, ' ');
		if (written == -1)
			return (-1);
		total_len += written;
	}
	return (total_len);
}

int	ft_print_string(t_format fmt, char *str)
{
	const char	*nullstr;
	char		*processed_str;
	int			print_len;

	nullstr = "(null)";
	processed_str = handle_null_string(str, nullstr);
	print_len = ft_strlen(processed_str);
	if (fmt.dot == 1 && fmt.precision >= 0 && fmt.precision < print_len)
		print_len = fmt.precision;
	return (write_padded_string(fmt, processed_str, print_len));
}
