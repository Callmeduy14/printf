/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:29:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/22 10:59:28 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_padding(char *buffer, int *pos, int padding, char pad_char)
{
	while (*pos < padding)
	{
		buffer[*pos] = pad_char;
		(*pos)++;
	}
}

int	ft_print_char(t_format fmt, int c)
{
	char	buffer[256];
	int		pos;
	int		padding;

	pos = 0;
	padding = 0;
	if (fmt.width > 1)
		padding = fmt.width - 1;
	if (!fmt.minus && padding > 0)
		fill_padding(buffer, &pos, padding, ' ');
	buffer[pos] = (char)c;
	pos++;
	if (fmt.minus && padding > 0)
		fill_padding(buffer, &pos, fmt.width, ' ');
	if (write(1, buffer, pos) == -1)
		return (-1);
	return (pos);
}
