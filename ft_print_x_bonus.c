#include "ft_printf_bonus.h"
#include <stddef.h>

/*
 * ft_print_x_bonus.c
 *
 * Fungsi print_x_bonus mencetak unsigned int dalam heksadesimal (%x/%X)
 * dengan dukungan flag -, 0, #, width, precision, dan kombinasi sesuai subject 42 bonus.
 *
 * Aturan:
 * - Flag '#' untuk prefix 0x/0X jika value ≠ 0
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

// Fungsi untuk menghitung panjang heksadesimal
static int hexlen(unsigned int n) {
    int len = 1;
    while (n /= 16)
        len++;
    return len;
}

// Fungsi untuk print unsigned int dalam heksadesimal (rekursif)
static int puthex(unsigned int n, int upper) {
    int len = 0;
    char *base = upper ? "0123456789ABCDEF" : "0123456789abcdef";
    if (n >= 16)
        len += puthex(n / 16, upper);
    len += write(1, &base[n % 16], 1);
    return len;
}

// Fungsi utama print %x/%X versi bonus
int print_x_bonus(unsigned int n, t_fmt *fmt, int upper) {
    int numlen = (n == 0 && fmt->precision_specified && fmt->precision == 0) ? 0 : hexlen(n);
    int prefix = (fmt->flag_hash && n != 0) ? 2 : 0;
    int prec_pad = (fmt->precision_specified && fmt->precision > numlen) ? fmt->precision - numlen : 0;
    int content_len = numlen + prec_pad + prefix;
    int width_pad = (fmt->width > content_len) ? fmt->width - content_len : 0;
    int total = 0;

    // Padding kiri (spasi, jika tidak minus dan tidak zero)
    if (!fmt->flag_minus && (!fmt->flag_zero || fmt->precision_specified))
        total += putnchar(' ', width_pad);
    // Prefix 0x/0X jika flag #
    if (prefix)
        total += write(1, upper ? "0X" : "0x", 2);
    // Zero padding (flag 0, tanpa precision, tanpa minus)
    if (!fmt->flag_minus && fmt->flag_zero && !fmt->precision_specified)
        total += putnchar('0', width_pad);
    // Precision padding
    total += putnchar('0', prec_pad);
    // Angka (hanya jika tidak 0 dan precision 0)
    if (!(n == 0 && fmt->precision_specified && fmt->precision == 0))
        total += puthex(n, upper);
    // Padding kanan (jika minus)
    if (fmt->flag_minus)
        total += putnchar(' ', width_pad);
    return total;
} 