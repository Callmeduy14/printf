/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:33:26 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 17:26:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int ft_print_hex_value(unsigned long n, int lowercase)
{
    char *str;
    int count;
    int len;

    str = ft_xtoa(n, lowercase);
    if (!str)
        return (-1);

    len = ft_strlen(str);
    count = write(1, str, len);
    free(str);

    if (count == -1)
        return (-1);
    return (count);
}

static int ft_print_padding(int width, int len)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (i < width - len)
    {
        if (write(1, " ", 1) == -1)
            return (-1);
        count++;
        i++;
    }
    return (count);
}

static int ft_get_pointer_length(unsigned long ptr)
{
    char *temp_str;
    int len;

    if (ptr == 0)
        return (3); // "0x0" = 3 characters

    temp_str = ft_xtoa(ptr, 0);
    if (!temp_str)
        return (-1);
    len = ft_strlen(temp_str) + 2; // "0x" + hex digits
    free(temp_str);
    return (len);
}

static int ft_print_pointer_content(unsigned long ptr)
{
    int count;

    count = 0;
    if (write(1, "0x", 2) == -1)
        return (-1);
    count += 2;

    if (ptr == 0)
    {
        if (write(1, "0", 1) == -1)
            return (-1);
        count += 1;
    }
    else
    {
        int ret = ft_print_hex_value(ptr, 0);
        if (ret == -1)
            return (-1);
        count += ret;
    }
    return (count);
}

int ft_print_pointer(t_format fmt, unsigned long ptr)
{
    int total;
    int len;
    int ret;

    total = 0;
    if ((len = ft_get_pointer_length(ptr)) == -1)
        return (-1);
    if (!fmt.minus && fmt.width > len)
    {
        if ((ret = ft_print_padding(fmt.width, len)) == -1)
            return (-1);
        total += ret;
    }
    if ((ret = ft_print_pointer_content(ptr)) == -1)
        return (-1);
    total += ret;
    if (fmt.minus && fmt.width > len)
    {
        if ((ret = ft_print_padding(fmt.width, len)) == -1)
            return (-1);
        total += ret;
    }
    return (total);
}
