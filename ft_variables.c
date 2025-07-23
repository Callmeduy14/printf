/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:29:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 20:30:44 by yyudi            ###   ########.fr       */
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
