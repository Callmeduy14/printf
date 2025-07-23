/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:35:29 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 21:47:53 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_percent(t_format fmt)
{
	int	count;
	int	padding;

	count = 0;
	padding = fmt.width - 1;
	if (fmt.zero && !fmt.minus && padding > 0)
	{
		while (padding-- > 0)
			count += ft_putchar('0');
	}
	else if (!fmt.minus && padding > 0)
	{
		while (padding-- > 0)
			count += ft_putchar(' ');
	}
	count += ft_putchar('%');
	if (fmt.minus && padding > 0)
	{
		while (padding-- > 0)
			count += ft_putchar(' ');
	}
	return (count);
}

void	handle_sign_int(int n, t_format fmt, char *buf, int *pos)
{
	if (n < 0)
		buf[(*pos)++] = '-';
	else if (fmt.plus)
		buf[(*pos)++] = '+';
	else if (fmt.space)
		buf[(*pos)++] = ' ';
}
