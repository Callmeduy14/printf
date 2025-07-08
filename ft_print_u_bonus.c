#include "ft_printf_bonus.h"
#include <stddef.h>

/*
 * ft_print_u_bonus.c
 *
 * Fungsi print_u_bonus mencetak unsigned int (%u) dengan dukungan flag -, 0, width, precision,
 * dan kombinasi sesuai subject 42 bonus.
 *
 * Aturan:
 * - Flag '-' untuk left-justify (padding kanan)
 * - Flag '0' untuk zero-padding (tanpa precision, tanpa minus)
 * - Width untuk minimal lebar output (padding spasi/0)
 * - Precision untuk minimal digit angka (padding 0 di depan angka)
 * - Jika precision 0 dan n 0, tidak print apapun untuk angka
 */

// Fungsi untuk print karakter c sebanyak n kali (untuk padding)
static int putnchar(char c, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++)
        count += write(1, &c, 1);
    return count;
}

// Fungsi untuk menghitung panjang unsigned int
static int uintlen(unsigned int n) {
    int len = 1;
    while (n /= 10)
        len++;
    return len;
}

// Fungsi untuk print unsigned int dengan precision
static int putunbr_prec(unsigned int n, int prec) {
    int len = 0, numlen = uintlen(n);
    // Padding 0 untuk precision
    for (int i = 0; i < prec - numlen; i++)
        len += write(1, "0", 1);
    // Jika n == 0 dan precision == 0, tidak print apapun
    if (n == 0 && prec == 0)
        return len;
    if (n >= 10)
        len += putunbr_prec(n / 10, 0);
    len += write(1, &"0123456789"[n % 10], 1);
    return len;
}

// Fungsi utama print %u versi bonus
int print_u_bonus(unsigned int n, t_fmt *fmt) {
    int numlen = (n == 0 && fmt->precision_specified && fmt->precision == 0) ? 0 : uintlen(n);
    int prec_pad = (fmt->precision_specified && fmt->precision > numlen) ? fmt->precision - numlen : 0;
    int content_len = numlen + prec_pad;
    int width_pad = (fmt->width > content_len) ? fmt->width - content_len : 0;
    int total = 0;

    // Padding kiri (spasi, jika tidak minus dan tidak zero)
    if (!fmt->flag_minus && (!fmt->flag_zero || fmt->precision_specified))
        total += putnchar(' ', width_pad);
    // Zero padding (flag 0, tanpa precision, tanpa minus)
    if (!fmt->flag_minus && fmt->flag_zero && !fmt->precision_specified)
        total += putnchar('0', width_pad);
    // Precision padding
    total += putnchar('0', prec_pad);
    // Angka (hanya jika tidak 0 dan precision 0)
    if (!(n == 0 && fmt->precision_specified && fmt->precision == 0))
        total += putunbr_prec(n, 0);
    // Padding kanan (jika minus)
    if (fmt->flag_minus)
        total += putnchar(' ', width_pad);
    return total;
} 