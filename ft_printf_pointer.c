/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:33:26 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 11:12:29 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer_hex(unsigned long n)
{
	char	*str;  // ubah ke hex lowercase
	int	count;

	str = ft_xtoa(n, 0);
	count = 0;
	if (!str)
		return (-1);

	// pakai ft_strlen untuk hitung panjang string hex
	int len = (int)ft_strlen(str);

	// tulis string hex ke stdout
	if (write(1, str, len) == -1)
	{
		free(str);
		return (-1);
	}
	count = len;
	free(str);
	return (count);
}

int	ft_print_pointer(t_format fmt, unsigned long ptr)
{
	int	count;  // Total karakter yang sudah dicetak
	int	len;		// Panjang string hasil konversi pointer + prefix "0x"
	int	pad;		// Banyaknya spasi untuk padding (jika width > panjang string)
	int	i;		  // Variabel iterator untuk loop

	char *str;	  // String hasil konversi pointer ke hex (tanpa prefix "0x")

	count = 0;
	// Jika pointer NULL (0), string yang dicetak hanya "0"
	if (ptr == 0)
		str = "0";
	else
	{
		// Jika bukan NULL, konversi pointer ke string hex lowercase
		str = ft_xtoa(ptr, 0);
		if (!str)   // Jika malloc gagal, return error
			return (-1);
	}

	// Hitung panjang string hex + 2 karakter untuk "0x"
	len = (int)ft_strlen(str) + 2;

	pad = 0; // Inisialisasi padding spasi
	// Jika lebar field (width) lebih besar dari panjang string, hitung paddingnya
	if (fmt.width > len)
		pad = fmt.width - len;

	// Jika flag minus tidak aktif (artinya padding di kiri)
	if (!fmt.minus)
	{
		// Tulis spasi sebanyak pad ke stdout sebagai padding kiri
		for (i = 0; i < pad; i++)
		{
			if (write(1, " ", 1) == -1)
			{
				// Jika terjadi error saat menulis, free memori jika perlu lalu return error
				if (ptr != 0)
					free(str);
				return (-1);
			}
			count++; // Tambah jumlah karakter yang dicetak
		}
	}

	// Tulis prefix "0x" untuk menunjukan bahwa ini pointer hex
	if (write(1, "0x", 2) == -1)
	{
		if (ptr != 0)
			free(str);
		return (-1);
	}
	count += 2;

	// Tulis string hex pointer ke stdout
	if (write(1, str, ft_strlen(str)) == -1)
	{
		if (ptr != 0)
			free(str);
		return (-1);
	}
	count += ft_strlen(str);

	// Jika flag minus aktif (padding di kanan), tulis spasi setelah string
	if (fmt.minus)
	{
		for (i = 0; i < pad; i++)
		{
			if (write(1, " ", 1) == -1)
			{
				if (ptr != 0)
					free(str);
				return (-1);
			}
			count++;
		}
	}

	// Jika pointer bukan NULL, maka string hasil konversi dialokasikan di heap
	// Jadi harus di-free untuk menghindari memory leak
	if (ptr != 0)
		free(str);

	return (count); // Kembalikan total karakter yang sudah dicetak
}

