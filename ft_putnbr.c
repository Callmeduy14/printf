/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:03:03 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/16 10:03:05 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int ft_putnbr(int n)
{
    int count = 0;
    char c;
    if (n == -2147483648)
        return write(1, "-2147483648", 11);
    if (n < 0)
    {
        count += ft_putchar('-');
        n = -n;
    }
    if (n > 9)
        count += ft_putnbr(n / 10);
    c = n % 10 + '0';
    count += ft_putchar(c);
    return count;
}

static int ft_putunbr(unsigned int n)
{
    int count = 0;
    char c;
    if (n > 9)
        count += ft_putunbr(n / 10);
    c = n % 10 + '0';
    count += ft_putchar(c);
    return count;
}

static int ft_puthex(unsigned long n, int upper)
{
    int count = 0;
    char *base;
    base = upper ? "0123456789ABCDEF" : "0123456789abcdef";
    if (n >= 16)
        count += ft_puthex(n / 16, upper);
    count += ft_putchar(base[n % 16]);
    return count;
}

static int ft_putptr(void *ptr)
{
    int count = 0;
    unsigned long addr = (unsigned long)ptr;
    count += ft_putstr("0x");
    count += ft_puthex(addr, 0);
    return count;
}
