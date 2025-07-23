/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 21:07:52 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 21:04:52 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	write_hex_to_buffer(t_format *fmt, t_intvars *v,
		char *buffer, unsigned int n)
{
	char	*hex;

	hex = v->hex;
	if (!fmt->minus && v->pad_char == '0')
		write_prefix(fmt, v, buffer, n);
	if (!fmt->minus)
	{
		while (v->pad_space-- > 0)
			buffer[v->pos++] = v->pad_char;
	}
	if (!(!fmt->minus && v->pad_char == '0'))
		write_prefix(fmt, v, buffer, n);
	write_content(v, hex, buffer, fmt);
	if (fmt->minus)
	{
		while (v->pad_space-- > 0)
			buffer[v->pos++] = ' ';
	}
	return (v->pos);
}

static int	alloc_and_write_hex(t_format *fmt, t_intvars *v,
			char *hex, unsigned int n)
{
	size_t	buffer_size;
	char	*buffer;
	int		len;

	buffer_size = v->pad_space + v->pad_zero + ft_strlen(hex) + 4;
	buffer = malloc(buffer_size);
	if (!buffer)
		return (-1);
	v->hex = hex;
	len = write_hex_to_buffer(fmt, v, buffer, n);
	if (write(1, buffer, len) == -1)
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	return (len);
}

int	ft_print_hex(t_format fmt, unsigned int n)
{
	char		*hex;
	t_intvars	v;
	int			len;

	v.pos = 0;
	init_hex_vars(&fmt, n, &v, &hex);
	if (!hex)
		return (-1);
	calculate_hex_padding(&fmt, &v, n);
	len = alloc_and_write_hex(&fmt, &v, hex, n);
	free(hex);
	return (len);
}
