/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:47:53 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 14:07:42 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Menghitung panjang unsigned integer
** Return: jumlah digit
*/
static int	ft_unsigned_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1); // Jika 0, panjang 1
	while (n != 0)
	{
		n /= 10; // Bagi 10 untuk mengurangi digit
		len++;   // Tambah jumlah digit
	}
	return (len); // Return jumlah digit
}

/*
** Mengubah unsigned integer ke string
** Return: pointer ke string hasil konversi (harus di-free)
*/
char	*ft_utoa(unsigned int n)
{
	char	*str; // Buffer hasil konversi
	int		len; // Panjang digit
	int		i;   // Indeks

	len = ft_unsigned_len(n); // Hitung panjang digit
	str = (char *)malloc(sizeof(char) * (len + 1)); // Alokasi buffer
	if (str == NULL)
		return (NULL); // Jika gagal alokasi
	i = len - 1;
	if (n == 0)
		str[i] = '0'; // Jika 0, isi '0'
	while (n != 0)
	{
		str[i] = (n % 10) + '0'; // Ambil digit terakhir
		n /= 10;
		i--;
	}
	str[len] = '\0'; // Null-terminate
	return (str); // Return string hasil konversi
}

/*
** Menghitung panjang bilangan hexadecimal
** Return: jumlah digit hex
*/
static int	ft_hex_len(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1); // Jika 0, panjang 1
	while (n != 0)
	{
		n /= 16; // Bagi 16 untuk mengurangi digit
		len++;   // Tambah jumlah digit
	}
	return (len); // Return jumlah digit
}

/*
** Mengubah bilangan ke string hexadecimal
** uppercase: 1 untuk huruf besar, 0 untuk huruf kecil
** Return: pointer ke string hasil konversi (harus di-free)
*/
char	*ft_xtoa(unsigned long n, int uppercase)
{
	char	*str;      // Buffer hasil konversi
	int		len;      // Panjang digit
	int		i;        // Indeks
	char	*hex_chars;// Karakter hex

	if (uppercase)
		hex_chars = "0123456789ABCDEF"; // Huruf besar
	else
		hex_chars = "0123456789abcdef"; // Huruf kecil
	len = ft_hex_len(n); // Hitung panjang digit
	str = (char *)malloc(sizeof(char) * (len + 1)); // Alokasi buffer
	if (str == NULL)
		return (NULL); // Jika gagal alokasi
	str[len] = '\0'; // Null-terminate
	if (n == 0)
		str[0] = '0'; // Jika 0, isi '0'
	i = len - 1;
	while (n != 0)
	{
		str[i] = hex_chars[n % 16]; // Ambil digit hex terakhir
		n /= 16;
		i--;
	}
	return (str); // Return string hasil konversi
}
