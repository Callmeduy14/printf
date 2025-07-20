/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:07:17 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/20 16:13:53 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_print_char(t_format fmt, int c)
{
    char buffer[256];  // Buffer cukup untuk menampung karakter + padding
    int pos = 0;       // Posisi penulisan dalam buffer
    int padding = 0;   // Jumlah padding yang dibutuhkan
    char ch = (char)c; // Konversi ke char

    // Hitung jumlah padding jika width > 1
    if (fmt.width > 1)
        padding = fmt.width - 1;

    // Right alignment (padding sebelum karakter)
    if (!fmt.minus && padding > 0)
    {
        // Isi buffer dengan spasi untuk padding
        while (pos < padding)
        {
            buffer[pos] = ' ';
            pos++;
        }
    }

    // Tambahkan karakter utama ke buffer
    buffer[pos] = ch;
    pos++;

    // Left alignment (padding setelah karakter)
    if (fmt.minus && padding > 0)
    {
        // Isi buffer dengan spasi untuk padding
        while (pos < fmt.width)
        {
            buffer[pos] = ' ';
            pos++;
        }
    }

    // Tulis seluruh buffer sekaligus
    if (write(1, buffer, pos) == -1)
        return -1;

    return pos;
}

int ft_print_string(t_format fmt, char *str)
{
    char buffer[1024]; // Buffer cukup besar untuk string panjang
    int pos = 0;       // Posisi penulisan dalam buffer
    const char *nullstr = "(null)";
    int print_len;     // Panjang string yang akan dicetak
    int pad_space;     // Jumlah padding yang dibutuhkan

    // Handle string NULL
    if (!str)
        str = (char *)nullstr;

    // Hitung panjang string
    print_len = ft_strlen(str);

    // Apply precision jika ada
    if (fmt.dot == 1 && fmt.precision >= 0 && fmt.precision < print_len)
        print_len = fmt.precision;

    // Hitung padding space
    pad_space = fmt.width - print_len;
    if (pad_space < 0)
        pad_space = 0;

    // Right alignment (padding sebelum string)
    if (!fmt.minus && pad_space > 0)
    {
        // Isi buffer dengan spasi
        while (pos < pad_space)
        {
            buffer[pos] = ' ';
            pos++;
        }
    }

    // Salin string ke buffer
    ft_memcpy(buffer + pos, str, print_len);
    pos += print_len;

    // Left alignment (padding setelah string)
    if (fmt.minus && pad_space > 0)
    {
        // Isi buffer dengan spasi
        while (pos < fmt.width)
        {
            buffer[pos] = ' ';
            pos++;
        }
    }

    // Tulis seluruh buffer sekaligus
    if (write(1, buffer, pos) == -1)
        return -1;

    return pos;
}


int ft_print_pointer_hex(unsigned long n)
{
	char *str = ft_xtoa(n, 0);  // ubah ke hex lowercase
	int count = 0;

	if (!str)
		return -1;

	// pakai ft_strlen untuk hitung panjang string hex
	int len = (int)ft_strlen(str);

	// tulis string hex ke stdout
	if (write(1, str, len) == -1)
	{
		free(str);
		return -1;
	}
	count = len;
	free(str);
	return count;
}

int ft_print_pointer(t_format fmt, unsigned long ptr)
{
	int count = 0;  // Total karakter yang sudah dicetak
	int len;		// Panjang string hasil konversi pointer + prefix "0x"
	int pad;		// Banyaknya spasi untuk padding (jika width > panjang string)
	int i;		  // Variabel iterator untuk loop

	char *str;	  // String hasil konversi pointer ke hex (tanpa prefix "0x")

	// Jika pointer NULL (0), string yang dicetak hanya "0"
	if (ptr == 0)
		str = "0";
	else
	{
		// Jika bukan NULL, konversi pointer ke string hex lowercase
		str = ft_xtoa(ptr, 0);
		if (!str)   // Jika malloc gagal, return error
			return -1;
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
				return -1;
			}
			count++; // Tambah jumlah karakter yang dicetak
		}
	}

	// Tulis prefix "0x" untuk menunjukan bahwa ini pointer hex
	if (write(1, "0x", 2) == -1)
	{
		if (ptr != 0)
			free(str);
		return -1;
	}
	count += 2;

	// Tulis string hex pointer ke stdout
	if (write(1, str, ft_strlen(str)) == -1)
	{
		if (ptr != 0)
			free(str);
		return -1;
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
				return -1;
			}
			count++;
		}
	}

	// Jika pointer bukan NULL, maka string hasil konversi dialokasikan di heap
	// Jadi harus di-free untuk menghindari memory leak
	if (ptr != 0)
		free(str);

	return count; // Kembalikan total karakter yang sudah dicetak
}


int ft_print_int(t_format fmt, int n)
{
    char buffer[256];  // Buffer cukup untuk angka panjang
    int pos = 0;       // Posisi penulisan dalam buffer
    char *num;         // String hasil konversi angka
    int is_neg = 0;    // Flag angka negatif
    int print_sign = 0;// Flag perlu tanda +/spasi
    int pad_zero = 0;  // Jumlah zero padding
    int pad_space = 0; // Jumlah space padding
    int len = 0;       // Panjang digit
    char pad_char;     // Karakter padding (' ' atau '0')

    // Konversi angka ke string
    num = ft_itoa(n);
    if (!num)
        return -1;

    // Tentukan flag negatif
    if (n < 0)
        is_neg = 1;

    // Hitung panjang digit (abaikan tanda minus)
    len = ft_strlen(num);
    if (is_neg)
        len--;

    // Handle kasus precision 0 dan angka 0
    if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
        len = 0;

    // Hitung zero padding dari precision
    if (fmt.dot == 1 && fmt.precision > len)
        pad_zero = fmt.precision - len;

    // Tentukan apakah perlu tanda + atau spasi
    if (is_neg || fmt.plus || fmt.space)
        print_sign = 1;

    // Hitung total panjang output
    int total_len = print_sign + pad_zero + len;

    // Hitung space padding dari width
    if (fmt.width > total_len)
        pad_space = fmt.width - total_len;

    // Tentukan karakter padding
    pad_char = ' ';
    if (fmt.zero && !fmt.minus && !fmt.dot)
        pad_char = '0';

    // Right alignment (padding sebelum konten)
    if (!fmt.minus)
    {
        // Jika padding dengan '0', cetak tanda dulu
        if (pad_char == '0' && print_sign)
        {
            if (is_neg)
                buffer[pos++] = '-';
            else if (fmt.plus)
                buffer[pos++] = '+';
            else if (fmt.space)
                buffer[pos++] = ' ';
            print_sign = 0;
        }

        // Isi padding space/zero
        while (pad_space > 0)
        {
            buffer[pos++] = pad_char;
            pad_space--;
        }
    }

    // Cetak tanda jika belum dicetak
    if (print_sign)
    {
        if (is_neg)
            buffer[pos++] = '-';
        else if (fmt.plus)
            buffer[pos++] = '+';
        else if (fmt.space)
            buffer[pos++] = ' ';
    }

    // Isi zero padding dari precision
    while (pad_zero > 0)
    {
        buffer[pos++] = '0';
        pad_zero--;
    }

    // Cetak digit (kecuali precision=0 dan n=0)
    if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0))
    {
        // Lewati tanda '-' jika ada
        char *digits = num;
        if (is_neg)
            digits++;

        // Salin digit ke buffer
        while (*digits)
        {
            buffer[pos++] = *digits;
            digits++;
        }
    }

    // Left alignment (padding setelah konten)
    if (fmt.minus)
    {
        while (pad_space > 0)
        {
            buffer[pos++] = ' ';
            pad_space--;
        }
    }

    free(num);

    // Tulis seluruh buffer sekaligus
    if (write(1, buffer, pos) == -1)
        return -1;

    return pos;
}

int ft_print_unsigned(t_format fmt, unsigned int n)
{
    char buffer[256];  // Buffer cukup untuk unsigned int terbesar
    int pos = 0;       // Posisi penulisan dalam buffer
    char *num;         // String hasil konversi
    int len = 0;       // Panjang digit
    int pad_zero = 0;  // Jumlah zero padding
    int pad_space = 0; // Jumlah space padding
    int i;

    // Konversi angka ke string
    num = ft_utoa(n);
    if (!num)
        return -1;

    // Hitung panjang digit
    i = 0;
    while (num[i])
        i++;
    len = i;

    // Handle kasus precision 0 dan angka 0
    if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
        len = 0;

    // Hitung zero padding dari precision
    if (fmt.dot == 1 && fmt.precision > len)
        pad_zero = fmt.precision - len;

    // Hitung total panjang output
    int total = pad_zero + len;
    if (len == 0)
        total = 0;

    // Hitung space padding dari width
    if (fmt.width > total)
        pad_space = fmt.width - total;

    // Tentukan karakter padding
    char pad_char = ' ';
    if (fmt.zero && fmt.dot == 0)
        pad_char = '0';

    // Right alignment (padding sebelum konten)
    if (!fmt.minus && pad_space > 0)
    {
        // Isi buffer dengan padding karakter
        while (pad_space > 0)
        {
            buffer[pos++] = pad_char;
            pad_space--;
        }
    }

    // Isi zero padding dari precision
    while (pad_zero > 0)
    {
        buffer[pos++] = '0';
        pad_zero--;
    }

    // Cetak digit (kecuali precision=0 dan n=0)
    if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0))
    {
        // Salin digit ke buffer
        i = 0;
        while (num[i])
        {
            buffer[pos++] = num[i];
            i++;
        }
    }

    // Left alignment (padding setelah konten)
    if (fmt.minus && pad_space > 0)
    {
        // Isi buffer dengan spasi
        while (pad_space > 0)
        {
            buffer[pos++] = ' ';
            pad_space--;
        }
    }

    free(num);

    // Tulis seluruh buffer sekaligus
    if (write(1, buffer, pos) == -1)
        return -1;

    return pos;
}

int ft_print_hex(t_format fmt, unsigned int n, int uppercase)
{
    char buffer[256];  // Buffer cukup untuk hex panjang
    int pos = 0;       // Posisi penulisan dalam buffer
    char *hex;         // String hasil konversi hex
    int prefix = 0;    // Flag prefix "0x"/"0X"
    int pad_zero = 0;  // Jumlah zero padding
    int pad_space = 0; // Jumlah space padding
    int len = 0;       // Panjang digit hex
    char pad_char;     // Karakter padding (' ' atau '0')

    // Konversi angka ke string hex
    hex = ft_xtoa(n, uppercase);
    if (!hex)
        return -1;

    // Hitung panjang digit hex
    len = ft_strlen(hex);

    // Handle kasus precision 0 dan angka 0
    if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
        len = 0;

    // Hitung zero padding dari precision
    if (fmt.dot == 1 && fmt.precision > len)
        pad_zero = fmt.precision - len;

    // Tentukan perlu prefix "0x" atau "0X"
    if (fmt.hash && n != 0)
        prefix = 2;

    // Hitung total panjang output
    int total_len = prefix + pad_zero + len;

    // Hitung space padding dari width
    if (fmt.width > total_len)
        pad_space = fmt.width - total_len;

    // Tentukan karakter padding
    pad_char = ' ';
    if (fmt.zero && !fmt.minus && !fmt.dot)
        pad_char = '0';

    // Right alignment (padding sebelum konten)
    if (!fmt.minus)
    {
        // Jika padding dengan '0', cetak prefix dulu
        if (pad_char == '0' && prefix)
        {
            buffer[pos++] = '0';
            if (uppercase)
                buffer[pos++] = 'X';
            else
                buffer[pos++] = 'x';
            prefix = 0;
        }

        // Isi padding space/zero
        while (pad_space > 0)
        {
            buffer[pos++] = pad_char;
            pad_space--;
        }
    }

    // Cetak prefix jika belum dicetak
    if (prefix)
    {
        buffer[pos++] = '0';
        if (uppercase)
            buffer[pos++] = 'X';
        else
            buffer[pos++] = 'x';
    }

    // Isi zero padding dari precision
    while (pad_zero > 0)
    {
        buffer[pos++] = '0';
        pad_zero--;
    }

    // Cetak digit hex (kecuali precision=0 dan n=0)
    if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0))
    {
        // Salin digit hex ke buffer
        int i = 0;
        while (hex[i])
        {
            buffer[pos++] = hex[i];
            i++;
        }
    }

    // Left alignment (padding setelah konten)
    if (fmt.minus)
    {
        while (pad_space > 0)
        {
            buffer[pos++] = ' ';
            pad_space--;
        }
    }

    free(hex);

    // Tulis seluruh buffer sekaligus
    if (write(1, buffer, pos) == -1)
        return -1;

    return pos;
}


int ft_print_percent(t_format fmt)
{
	(void)fmt;
	if (write(1, "%", 1) == -1)
		return (-1);
	return (1);
}
