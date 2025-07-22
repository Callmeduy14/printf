/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:43:45 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 17:38:22 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Inisialisasi variabel untuk konversi dan padding integer
static void	init_int_vars(int n, t_format fmt, t_intvars *v, char *num)
{
	v->is_neg = (n < 0); // Cek apakah angka negatif
	v->len = ft_strlen(num); // Panjang string angka
	if (v->is_neg)
		v->len--; // Jika negatif, kurangi 1 (karena tanda '-')
	// Jika precision 0 dan n=0, tidak ada digit yang dicetak
	if (fmt.dot && fmt.precision == 0 && n == 0)
		v->len = 0;
	v->pad_zero = 0; // Jumlah padding nol
	// Hitung padding nol jika precision lebih besar dari digit
	if (fmt.dot && fmt.precision > v->len)
		v->pad_zero = fmt.precision - v->len;
	// Perlu cetak tanda jika negatif, plus, atau space
	v->print_sign = (v->is_neg || fmt.plus || fmt.space);
	v->pad_space = 0; // Jumlah padding spasi
	if (fmt.width > (v->print_sign + v->pad_zero + v->len))
		v->pad_space = fmt.width - (v->print_sign + v->pad_zero + v->len);
	v->pad_char = ' '; // Default padding spasi
	// Gunakan '0' jika flag zero aktif dan tidak ada minus/dot
	if (fmt.zero && !fmt.minus && !fmt.dot)
		v->pad_char = '0';
	v->pos = 0; // Posisi buffer
}

// Menulis tanda (+, -, spasi) ke buffer jika diperlukan
static void	handle_sign(int n, t_format fmt, char *buf, int *pos)
{
	if (n < 0)
		buf[(*pos)++] = '-'; // Tulis tanda minus
	else if (fmt.plus)
		buf[(*pos)++] = '+'; // Tulis tanda plus
	else if (fmt.space)
		buf[(*pos)++] = ' '; // Tulis spasi
}

// Mengisi buffer dengan karakter padding (spasi/0)
static void	handle_padding(int count, char c, char *buf, int *pos)
{
	while (count-- > 0)
		buf[(*pos)++] = c; // Isi buffer dengan karakter c
}

// Menyalin digit angka ke buffer, skip tanda jika negatif
static void	copy_digits(char *num, int is_neg, char *buf, int *pos)
{
	char	*d;
	d = num;
	if (is_neg)
		d++; // Lewati tanda minus
	while (*d)
		buf[(*pos)++] = *d++; // Salin digit ke buffer
}

// Fungsi utama untuk mencetak integer dengan format
int	ft_print_int(t_format fmt, int n)
{
	char		buffer[256]; // Buffer hasil akhir
	t_intvars	v;         // Variabel bantu
	char		*num;       // String hasil konversi angka

	num = ft_itoa(n); // Konversi int ke string
	if (!num)
		return (-1); // Jika gagal alokasi
	init_int_vars(n, fmt, &v, num); // Inisialisasi variabel bantu
	// Jika padding char '0' dan perlu tanda, tulis tanda dulu
	if (!fmt.minus && v.pad_char == '0' && v.print_sign)
		handle_sign(n, fmt, buffer, &v.pos);
	// Padding spasi/0 di depan
	if (!fmt.minus)
		handle_padding(v.pad_space, v.pad_char, buffer, &v.pos);
	// Jika left align atau padding char spasi, tulis tanda setelah padding
	if (v.print_sign && (fmt.minus || v.pad_char != '0'))
		handle_sign(n, fmt, buffer, &v.pos);
	// Padding nol di depan digit
	handle_padding(v.pad_zero, '0', buffer, &v.pos);
	// Salin digit angka (skip jika precision 0 dan n=0)
	if (!(fmt.dot && fmt.precision == 0 && n == 0))
		copy_digits(num, v.is_neg, buffer, &v.pos);
	// Padding spasi di belakang jika left align
	if (fmt.minus)
		handle_padding(v.pad_space, ' ', buffer, &v.pos);
	free(num); // Bebaskan memori
	// Tulis hasil ke stdout
	if (write(1, buffer, v.pos) == -1)
		return (-1);
	return (v.pos); // Return jumlah karakter yang dicetak
}
