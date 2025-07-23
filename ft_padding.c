/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:52:10 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 21:31:51 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_padding_int(int count, char c, char *buf, int *pos)
{
	while (count-- > 0)
		buf[(*pos)++] = c;
}

void	handle_padding_unsign(char *buffer, int *pos, int pad, char c)
{
	while (pad-- > 0)
		buffer[(*pos)++] = c;
}

int	calculate_unsigned_padding(t_format fmt, int len,
	unsigned int n, int *paddings)
{
	int	total;

	paddings[0] = 0;
	paddings[1] = 0;
	if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
		len = 0;
	if (fmt.dot == 1 && fmt.precision > len)
		paddings[0] = fmt.precision - len;
	total = paddings[0] + len;
	if (len == 0)
		total = 0;
	if (fmt.width > total)
		paddings[1] = fmt.width - total;
	return (total);
}

int	calculate_hex_padding(t_format *fmt, t_intvars *v, unsigned int n)
{
	int	total_len;

	total_len = 0;
	if (fmt->hash && n != 0)
		total_len += 2;
	total_len += v->pad_zero + v->len;
	v->pad_space = 0;
	if (fmt->width > total_len)
		v->pad_space = fmt->width - total_len;
	return (v->pad_space);
}

int	calculate_string_padding(t_format fmt, int print_len)
{
	int	pad_space;

	pad_space = fmt.width - print_len;
	if (pad_space < 0)
		pad_space = 0;
	return (pad_space);
}
