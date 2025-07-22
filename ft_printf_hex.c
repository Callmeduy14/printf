/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 20:26:39 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Inisialisasi variabel untuk konversi dan padding hex
static void	init_hex_vars(t_format *fmt, unsigned int n, t_intvars *v, char **hex)
{
	v->is_neg = 0; // Hex tidak pernah negatif
	v->print_sign = 0; // Tidak ada tanda untuk hex
	*hex = ft_xtoa(n, (fmt->type == 'X')); // Konversi angka ke string hex (huruf besar/kecil)
	if (!*hex)
		return; // Jika gagal alokasi
	v->len = ft_strlen(*hex); // Panjang string hex
	// Jika precision 0 dan n=0, tidak ada digit yang dicetak
	if (fmt->dot && fmt->precision == 0 && n == 0)
		v->len = 0;
	v->pad_zero = 0; // Jumlah padding nol
	// Hitung padding nol jika precision lebih besar dari digit
	if (fmt->dot && fmt->precision > v->len)
		v->pad_zero = fmt->precision - v->len;
	v->pad_char = ' '; // Default padding spasi
	// Gunakan '0' jika flag zero aktif dan tidak ada minus/dot
	if (fmt->zero && !fmt->minus && !fmt->dot)
		v->pad_char = '0';
}

// Hitung padding spasi untuk hex
static void	calculate_padding(t_format *fmt, t_intvars *v, unsigned int n)
{
	int	total_len;
	total_len = 0;
	// Tambah 2 jika ada hash dan n != 0 (untuk '0x'/'0X')
	if (fmt->hash && n != 0)
		total_len += 2;
	total_len += v->pad_zero + v->len; // Total panjang yang akan dicetak
	v->pad_space = 0; // Jumlah padding spasi
	if (fmt->width > total_len)
		v->pad_space = fmt->width - total_len;
}

// Menulis prefix '0x' atau '0X' jika hash aktif
static void	write_prefix(t_format *fmt, t_intvars *v, char *buffer, unsigned int n)
{
	if (fmt->hash && n != 0)
	{
		buffer[v->pos++] = '0'; // Tulis '0'
		if (fmt->type == 'X')
			buffer[v->pos++] = 'X'; // Tulis 'X' jika hex besar
		else
			buffer[v->pos++] = 'x'; // Tulis 'x' jika hex kecil
	}
}

// Menulis digit hex dan padding nol ke buffer
static void	write_content(t_intvars *v, char *hex, char *buffer, t_format *fmt)
{
	while (v->pad_zero-- > 0)
		buffer[v->pos++] = '0'; // Isi padding nol
	// Jika bukan kasus precision 0 dan hex = 0
	if (!(fmt->dot && fmt->precision == 0 && hex[0] == '0'))
	{
		while (*hex)
			buffer[v->pos++] = *hex++; // Salin digit hex ke buffer
	}
}

// Fungsi utama untuk mencetak unsigned integer dalam format hex
int	ft_print_hex(t_format fmt, unsigned int n)
{
	char		buffer[256]; // Buffer hasil akhir
	char		*hex;        // String hasil konversi hex
	t_intvars	v;          // Variabel bantu

	v.pos = 0; // Inisialisasi posisi buffer
	init_hex_vars(&fmt, n, &v, &hex); // Inisialisasi variabel bantu
	if (!hex)
		return (-1); // Jika gagal alokasi
	calculate_padding(&fmt, &v, n); // Hitung padding spasi
	// Jika padding char '0' dan right align, prefix di depan
	if (!fmt.minus && v.pad_char == '0')
		write_prefix(&fmt, &v, buffer, n);
	// Padding spasi di depan
	if (!fmt.minus)
		while (v.pad_space-- > 0)
			buffer[v.pos++] = v.pad_char;
	// Jika bukan kasus di atas, prefix setelah spasi
	if (!(!fmt.minus && v.pad_char == '0'))
		write_prefix(&fmt, &v, buffer, n);
	// Tulis digit hex dan padding nol
	write_content(&v, hex, buffer, &fmt);
	// Padding spasi di belakang jika left align
	if (fmt.minus)
		while (v.pad_space-- > 0)
			buffer[v.pos++] = ' ';
	free(hex); // Bebaskan memori
	// Tulis hasil ke stdout
	if (write(1, buffer, v.pos) == -1)
		return (-1);
	return (v.pos); // Return jumlah karakter yang dicetak
}
