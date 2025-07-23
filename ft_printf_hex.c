/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/22 11:00:37 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_hex_vars(t_format *fmt, unsigned int n,
			t_intvars *v, char **hex)
{
	v->is_neg = 0;
	v->print_sign = 0;
	*hex = ft_xtoa(n, (fmt->type == 'X'));
	if (!*hex)
		return ;
	v->len = ft_strlen(*hex);
	if (fmt->dot && fmt->precision == 0 && n == 0)
		v->len = 0;
	v->pad_zero = 0;
	if (fmt->dot && fmt->precision > v->len)
		v->pad_zero = fmt->precision - v->len;
	v->pad_char = ' ';
	if (fmt->zero && !fmt->minus && !fmt->dot)
		v->pad_char = '0';
}

static void	calculate_padding(t_format *fmt, t_intvars *v, unsigned int n)
{
	int	total_len;

	total_len = 0;
	if (fmt->hash && n != 0)
		total_len += 2;
	total_len += v->pad_zero + v->len;
	v->pad_space = 0;
	if (fmt->width > total_len)
		v->pad_space = fmt->width - total_len;
}

static void	write_prefix(t_format *fmt, t_intvars *v, char *buffer,
			unsigned int n)
{
	if (fmt->hash && n != 0)
	{
		buffer[v->pos++] = '0';
		if (fmt->type == 'X')
			buffer[v->pos++] = 'X';
		else
			buffer[v->pos++] = 'x';
	}
}

static void	write_content(t_intvars *v, char *hex, char *buffer, t_format *fmt)
{
	while (v->pad_zero-- > 0)
		buffer[v->pos++] = '0';
	if (!(fmt->dot && fmt->precision == 0 && hex[0] == '0'))
	{
		while (*hex)
			buffer[v->pos++] = *hex++;
	}
}

int	ft_print_hex(t_format fmt, unsigned int n)
{
	char		buffer[256];
	char		*hex;
	t_intvars	v;

	v.pos = 0;
	init_hex_vars(&fmt, n, &v, &hex);
	if (!hex)
		return (-1);
	calculate_padding(&fmt, &v, n);
	if (!fmt.minus && v.pad_char == '0')
		write_prefix(&fmt, &v, buffer, n);
	if (!fmt.minus)
		while (v.pad_space-- > 0)
			buffer[v.pos++] = v.pad_char;
	if (!(!fmt.minus && v.pad_char == '0'))
		write_prefix(&fmt, &v, buffer, n);
	write_content(&v, hex, buffer, &fmt);
	if (fmt.minus)
		while (v.pad_space-- > 0)
			buffer[v.pos++] = ' ';
	free(hex);
	if (write(1, buffer, v.pos) == -1)
		return (-1);
	return (v.pos);
}
