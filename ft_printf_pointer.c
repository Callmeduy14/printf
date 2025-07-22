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

// Fungsi untuk mencetak nilai pointer dalam format hex (tanpa prefix)
static int ft_print_hex_value(unsigned long n, int lowercase)
{
    char *str; // String hasil konversi hex
    int count; // Jumlah karakter yang dicetak
    int len;   // Panjang string

    str = ft_xtoa(n, lowercase); // Konversi ke string hex
    if (!str)
        return (-1); // Jika gagal alokasi

    len = ft_strlen(str); // Hitung panjang string
    count = write(1, str, len); // Tulis string ke layar
    free(str); // Bebaskan memori

    if (count == -1)
        return (-1); // Jika gagal tulis
    return (count); // Return jumlah karakter yang dicetak
}

// Fungsi untuk mencetak padding spasi
static int ft_print_padding(int width, int len)
{
    int count = 0; // Jumlah karakter yang dicetak
    int i = 0;
    while (i < width - len) // Selama masih kurang dari width
    {
        if (write(1, " ", 1) == -1)
            return (-1); // Jika gagal tulis
        count++;
        i++;
    }
    return (count); // Return jumlah spasi yang dicetak
}

// Fungsi untuk mendapatkan panjang string pointer (termasuk prefix)
static int ft_get_pointer_length(unsigned long ptr)
{
    char *temp_str; // String hex sementara
    int len;

    if (ptr == 0)
        return (3); // "0x0" = 3 karakter

    temp_str = ft_xtoa(ptr, 0); // Konversi ke string hex
    if (!temp_str)
        return (-1);
    len = ft_strlen(temp_str) + 2; // "0x" + digit hex
    free(temp_str);
    return (len); // Return panjang total
}

// Fungsi untuk mencetak isi pointer (prefix + hex)
static int ft_print_pointer_content(unsigned long ptr)
{
    int count = 0; // Jumlah karakter yang dicetak

    if (write(1, "0x", 2) == -1)
        return (-1); // Tulis prefix
    count += 2;

    if (ptr == 0)
    {
        if (write(1, "0", 1) == -1)
            return (-1); // Tulis '0' jika NULL
        count += 1;
    }
    else
    {
        int ret = ft_print_hex_value(ptr, 0); // Cetak hex
        if (ret == -1)
            return (-1);
        count += ret;
    }
    return (count); // Return jumlah karakter yang dicetak
}

// Fungsi utama untuk mencetak pointer dengan format
int ft_print_pointer(t_format fmt, unsigned long ptr)
{
    int total; // Jumlah karakter yang dicetak
    int len;   // Panjang string pointer
    int ret;   // Return sementara

    total = 0;
    if ((len = ft_get_pointer_length(ptr)) == -1)
        return (-1); // Jika gagal alokasi
    if (!fmt.minus && fmt.width > len)
    {
        if ((ret = ft_print_padding(fmt.width, len)) == -1)
            return (-1); // Padding spasi di depan
        total += ret;
    }
    if ((ret = ft_print_pointer_content(ptr)) == -1)
        return (-1); // Cetak isi pointer
    total += ret;
    if (fmt.minus && fmt.width > len)
    {
        if ((ret = ft_print_padding(fmt.width, len)) == -1)
            return (-1); // Padding spasi di belakang
        total += ret;
    }
    return (total); // Return jumlah karakter yang dicetak
}
