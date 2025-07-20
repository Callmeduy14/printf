/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:47:53 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/20 13:43:15 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Menghitung panjang unsigned integer
** Return: jumlah digit
*/
static int ft_unsigned_len(unsigned int n)
{
    int len;
    len = 0;
    if (n == 0)
        return (1);
    while (n != 0)
    {
        n /= 10;
        len++;
    }
    return (len);
}

/*
** Mengubah unsigned integer ke string
** Return: pointer ke string hasil konversi (harus di-free)
*/
char *ft_utoa(unsigned int n)
{
    char    *str;
    int     len;
    int     i;
    len = ft_unsigned_len(n);
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return (NULL);
    i = len - 1;
    if (n == 0)
        str[i] = '0';
    while (n != 0)
    {
        str[i] = (n % 10) + '0';
        n /= 10;
        i--;
    }
    str[len] = '\0';
    return (str);
}

/*
** Menghitung panjang bilangan hexadecimal
** Return: jumlah digit hex
*/
static int ft_hex_len(unsigned long n)
{
    int len;
    len = 0;
    if (n == 0)
        return (1);
    while (n != 0)
    {
        n /= 16;
        len++;
    }
    return (len);
}

/*
** Mengubah bilangan ke string hexadecimal
** uppercase: 1 untuk huruf besar, 0 untuk huruf kecil
** Return: pointer ke string hasil konversi (harus di-free)
*/
char *ft_xtoa(unsigned long n, int uppercase)
{
    char    *str;
    int     len;
    int     i;
    char    *hex_chars;
    if (uppercase)
        hex_chars = "0123456789ABCDEF";
    else
        hex_chars = "0123456789abcdef";
    len = ft_hex_len(n);
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return (NULL);
	str[len] = '\0';
    if (n == 0)
        str[0] = '0';
	i = len - 1;
    while (n != 0)
    {
        str[i] = hex_chars[n % 16];
        n /= 16;
        i--;
    }
    return (str);
}
