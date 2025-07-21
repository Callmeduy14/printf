/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:43:45 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 17:38:22 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_int_vars(int n, t_format fmt, t_intvars *v, char *num)
{
	v->is_neg = (n < 0);
	v->len = ft_strlen(num);
	if (v->is_neg)
		v->len--;
	if (fmt.dot && fmt.precision == 0 && n == 0)
		v->len = 0;
	v->pad_zero = 0;
	if (fmt.dot && fmt.precision > v->len)
		v->pad_zero = fmt.precision - v->len;
	v->print_sign = (v->is_neg || fmt.plus || fmt.space);
	v->pad_space = 0;
	if (fmt.width > (v->print_sign + v->pad_zero + v->len))
		v->pad_space = fmt.width - (v->print_sign + v->pad_zero + v->len);
	v->pad_char = ' ';
	if (fmt.zero && !fmt.minus && !fmt.dot)
		v->pad_char = '0';
	v->pos = 0;
}

static void	handle_sign(int n, t_format fmt, char *buf, int *pos)
{
	if (n < 0)
		buf[(*pos)++] = '-';
	else if (fmt.plus)
		buf[(*pos)++] = '+';
	else if (fmt.space)
		buf[(*pos)++] = ' ';
}

static void	handle_padding(int count, char c, char *buf, int *pos)
{
	while (count-- > 0)
		buf[(*pos)++] = c;
}

static void	copy_digits(char *num, int is_neg, char *buf, int *pos)
{
	char	*d;

	d = num;
	if (is_neg)
		d++;
	while (*d)
		buf[(*pos)++] = *d++;
}

int	ft_print_int(t_format fmt, int n)
{
	char		buffer[256];
	t_intvars	v;
	char		*num;

	num = ft_itoa(n);
	if (!num)
		return (-1);
	init_int_vars(n, fmt, &v, num);
	if (!fmt.minus && v.pad_char == '0' && v.print_sign)
		handle_sign(n, fmt, buffer, &v.pos);
	if (!fmt.minus)
		handle_padding(v.pad_space, v.pad_char, buffer, &v.pos);
	if (v.print_sign && (fmt.minus || v.pad_char != '0'))
		handle_sign(n, fmt, buffer, &v.pos);
	handle_padding(v.pad_zero, '0', buffer, &v.pos);
	if (!(fmt.dot && fmt.precision == 0 && n == 0))
		copy_digits(num, v.is_neg, buffer, &v.pos);
	if (fmt.minus)
		handle_padding(v.pad_space, ' ', buffer, &v.pos);
	free(num);
	if (write(1, buffer, v.pos) == -1)
		return (-1);
	return (v.pos);
}
