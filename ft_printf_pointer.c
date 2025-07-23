/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:33:26 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/22 11:30:56 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_pointer_hex(unsigned long n, int *total)
{
	char	*str;
	int		ret;

	str = ft_xtoa(n, 0);
	if (!str)
		return (0);
	ret = write(1, str, ft_strlen(str));
	free(str);
	if (ret == -1)
		return (0);
	*total += ret;
	return (1);
}

static int	get_pointer_len(unsigned long ptr)
{
	char	*str;
	int		len;

	if (ptr == 0)
		return (3);
	str = ft_xtoa(ptr, 0);
	if (!str)
		return (-1);
	len = ft_strlen(str) + 2;
	free(str);
	return (len);
}

static int	print_pointer_content(unsigned long ptr, int *total)
{
	if (write(1, "0x", 2) == -1)
		return (0);
	*total += 2;
	if (ptr == 0)
	{
		if (write(1, "0", 1) == -1)
			return (0);
		(*total)++;
	}
	else if (!print_pointer_hex(ptr, total))
		return (0);
	return (1);
}

static int	print_pointer_padding(int width, int len, int *total)
{
	int	padding;

	padding = width - len;
	while (padding-- > 0)
	{
		if (write(1, " ", 1) == -1)
			return (0);
		(*total)++;
	}
	return (1);
}

int	ft_print_pointer(t_format fmt, unsigned long ptr)
{
	int	total;
	int	len;

	total = 0;
	len = get_pointer_len(ptr);
	if (len == -1)
		return (-1);
	if (!fmt.minus && fmt.width > len)
		if (!print_pointer_padding(fmt.width, len, &total))
			return (-1);
	if (!print_pointer_content(ptr, &total))
		return (-1);
	if (fmt.minus && fmt.width > len)
		if (!print_pointer_padding(fmt.width, len, &total))
			return (-1);
	return (total);
}
