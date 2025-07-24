/* ************************************************************************** */
/*                                                                            */
/*   File: ft_printf_char.c                                                    */
/*   Berisi fungsi untuk mencetak karakter dengan padding dan flag             */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Fungsi untuk menulis karakter padding sebanyak count kali ke stdout
// count: jumlah karakter yang ingin ditulis
// c: karakter padding (' ' atau '0')
// return: jumlah karakter yang berhasil ditulis, atau -1 jika error
int	write_padding(int count, char c)
{
	int	written; // Menyimpan hasil write per iterasi
	int	total;   // Total karakter yang sudah ditulis

	total = 0;
	while (count > 0)
	{
		written = write(1, &c, 1); // Tulis satu karakter padding
		if (written == -1)
			return (-1); // Jika gagal, return error
		total += written; // Tambah ke total
		count--;         // Kurangi sisa padding
	}
	return (total); // Kembalikan jumlah karakter yang ditulis
}

// Fungsi untuk handle padding sebelum karakter jika diperlukan
// fmt: hasil parsing format
// padding: jumlah padding yang dibutuhkan
// return: jumlah karakter padding yang ditulis
static int	handle_padding(t_format fmt, int padding)
{
	int	total;    // Total karakter padding
	char	pad_char; // Karakter padding (' ' atau '0')

	total = 0;
	pad_char = ' ';
	if (fmt.zero)
		pad_char = '0'; // Jika flag zero, gunakan '0' sebagai padding
	if (padding > 0)
	{
		if (!fmt.minus)
			total = write_padding(padding, pad_char); // Padding di kiri
	}
	return (total);
}

// Fungsi utama untuk mencetak karakter dengan format
// fmt: hasil parsing format
// c: karakter yang akan dicetak
// return: jumlah karakter yang dicetak
int	ft_print_char(t_format fmt, int c)
{
	int	total;   // Total karakter yang dicetak
	int	padding; // Jumlah padding yang dibutuhkan

	total = 0;
	padding = fmt.width - 1; // Hitung jumlah padding (width - 1 karakter)
	if (padding > 0)
		total = handle_padding(fmt, padding); // Padding sebelum karakter
	if (total == -1)
		return (-1); // Jika gagal padding, return error
	if (write(1, &c, 1) == -1)
		return (-1); // Cetak karakter utama
	total += 1; // Tambah satu karakter utama
	if (fmt.minus && padding > 0)
	{
		// Jika flag minus, padding di kanan
		if (write_padding(padding, ' ') == -1)
			return (-1);
		total += padding;
	}
	return (total);
}
