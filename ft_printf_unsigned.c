/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 20:27:07 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_padding(char *buffer, int *pos, int pad, char c)
{
	while (pad > 0)
	{
		buffer[(*pos)++] = c;
		pad--;
	}
}

static char	get_pad_char(t_format fmt)
{
	char	pad_char;

	pad_char = ' ';
	if (fmt.zero && fmt.dot == 0)
		pad_char = '0';
	return (pad_char);
}

static void	handle_number(char *buffer, int *pos, char *num, t_format fmt)
{
	int	i;

	i = 0;
	if (!(fmt.dot == 1 && fmt.precision == 0 && ft_atoi(num) == 0))
	{
		while (num[i])
		{
			buffer[(*pos)++] = num[i];
			i++;
		}
	}
}

int	ft_print_unsigned(t_format fmt, unsigned int n)
{
	char	buffer[256];
	int		pos;
	char	*num;
	int		paddings[2];
	char	pad_char;

	pos = 0;
	paddings[0] = 0;
	paddings[1] = 0;
	num = ft_utoa(n);
	if (!num)
		return (-1);
	calculate_unsigned_padding(fmt, ft_strlen(num), n, paddings);
	pad_char = get_pad_char(fmt);
	if (!fmt.minus && paddings[1] > 0)
		handle_padding(buffer, &pos, paddings[1], pad_char);
	handle_padding(buffer, &pos, paddings[0], '0');
	handle_number(buffer, &pos, num, fmt);
	if (fmt.minus && paddings[1] > 0)
		handle_padding(buffer, &pos, paddings[1], ' ');
	free(num);
	if (write(1, buffer, pos) == -1)
		return (-1);
	return (pos);
}
