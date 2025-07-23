/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:29:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 22:08:13 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_padding(int count, char c)
{
	int	written;
	int	total;

	total = 0;
	while (count > 0)
	{
		written = write(1, &c, 1);
		if (written == -1)
			return (-1);
		total += written;
		count--;
	}
	return (total);
}

static int	handle_padding(t_format fmt, int padding)
{
	int		total;
	char	pad_char;

	total = 0;
	pad_char = ' ';
	if (fmt.zero)
		pad_char = '0';
	if (padding > 0)
	{
		if (!fmt.minus)
			total = write_padding(padding, pad_char);
	}
	return (total);
}

int	ft_print_char(t_format fmt, int c)
{
	int	total;
	int	padding;

	total = 0;
	padding = fmt.width - 1;
	if (padding > 0)
		total = handle_padding(fmt, padding);
	if (total == -1)
		return (-1);
	if (write(1, &c, 1) == -1)
		return (-1);
	total += 1;
	if (fmt.minus && padding > 0)
	{
		if (write_padding(padding, ' ') == -1)
			return (-1);
		total += padding;
	}
	return (total);
}
