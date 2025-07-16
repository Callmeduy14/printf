/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:01:28 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/16 10:01:49 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

static int ft_putchar(char c)
{
    return write(1, &c, 1);
}

static int ft_putstr(const char *s)
{
    int len = 0;
    if (!s)
        s = "(null)";
    while (s[len])
        ft_putchar(s[len++]);
    return len;
}
