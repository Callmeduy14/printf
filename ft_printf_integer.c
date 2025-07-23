/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:43:45 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 21:24:24 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	copy_digits(char *num, int is_neg, char *buf, int *pos)
{
	char	*d;

	d = num;
	if (is_neg)
		d++;
	while (*d)
		buf[(*pos)++] = *d++;
}

static int	count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	estimate_output_size(t_format fmt, int n)
{
	int	digits;
	int	size;

	digits = count_digits(n);
	size = digits;
	if (fmt.precision > digits)
		size = fmt.precision;
	if (n < 0 || fmt.plus || fmt.space)
		size++;
	if (fmt.width > size)
		size = fmt.width;
	return (size);
}

static int	build_int_string(t_format fmt, int n, t_intvars *v, char *buffer)
{
	char	*num;

	num = ft_itoa(n);
	if (!num)
		return (-1);
	init_int_vars(n, fmt, v, num);
	if (!fmt.minus && v->pad_char == '0' && v->print_sign)
		handle_sign_int(n, fmt, buffer, &v->pos);
	if (!fmt.minus)
		handle_padding_int(v->pad_space, v->pad_char, buffer, &v->pos);
	if (v->print_sign && (fmt.minus || v->pad_char != '0'))
		handle_sign_int(n, fmt, buffer, &v->pos);
	handle_padding_int(v->pad_zero, '0', buffer, &v->pos);
	if (!(fmt.dot && fmt.precision == 0 && n == 0))
		copy_digits(num, v->is_neg, buffer, &v->pos);
	if (fmt.minus)
		handle_padding_int(v->pad_space, ' ', buffer, &v->pos);
	free(num);
	return (v->pos);
}

int	ft_print_int(t_format fmt, int n)
{
	char		*buffer;
	t_intvars	v;
	int			buffer_size;
	int			result;

	buffer_size = estimate_output_size(fmt, n);
	buffer = (char *)malloc(sizeof(char) * (buffer_size + 1));
	if (!buffer)
		return (-1);
	result = build_int_string(fmt, n, &v, buffer);
	if (result == -1)
	{
		free(buffer);
		return (-1);
	}
	if (write(1, buffer, result) == -1)
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	return (result);
}
