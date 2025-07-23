/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 21:52:15 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	get_pad_char(t_format fmt)
{
	char	pad_char;

	pad_char = ' ';
	if (fmt.zero && !fmt.dot)
		pad_char = '0';
	return (pad_char);
}

void	handle_number(char *buffer, int *pos, char *num, t_format fmt)
{
	int	i;

	i = 0;
	if (!(fmt.dot && fmt.precision == 0 && ft_atoi(num) == 0))
	{
		while (num[i])
			buffer[(*pos)++] = num[i++];
	}
}

static int	calculate_total_length(t_format fmt, int num_len, unsigned int n)
{
	int	total;

	total = num_len;
	if (fmt.precision > num_len)
		total = fmt.precision;
	if (fmt.width > total)
		total = fmt.width;
	if (fmt.dot && fmt.precision == 0 && n == 0)
		total = fmt.width;
	return (total);
}

static void	build_unsigned_str(char *str, t_format fmt,
			char *num, int paddings[2])
{
	int		pos;
	char	pad_char;

	pos = 0;
	pad_char = get_pad_char(fmt);
	if (!fmt.minus && paddings[1] > 0)
		handle_padding_unsign(str, &pos, paddings[1], pad_char);
	handle_padding_unsign(str, &pos, paddings[0], '0');
	handle_number(str, &pos, num, fmt);
	if (fmt.minus && paddings[1] > 0)
		handle_padding_unsign(str, &pos, paddings[1], ' ');
}

int	ft_print_unsigned(t_format fmt, unsigned int n)
{
	char	*num;
	char	*output;
	int		paddings[2];
	int		total_len;
	int		result;

	num = ft_utoa(n);
	if (!num)
		return (-1);
	calculate_unsigned_padding(fmt, ft_strlen(num), n, paddings);
	total_len = calculate_total_length(fmt, ft_strlen(num), n);
	output = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!output)
	{
		free(num);
		return (-1);
	}
	build_unsigned_str(output, fmt, num, paddings);
	free(num);
	result = write(1, output, total_len);
	free(output);
	if (result == -1)
		return (-1);
	return (total_len);
}
