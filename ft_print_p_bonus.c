#include "ft_printf_bonus.h"
#include <stddef.h>
#include <stdint.h>

/*
 * ft_print_p_bonus.c
 *
 * Fungsi print_p_bonus mencetak pointer (%p) dengan dukungan flag -, width, precision,
 * dan kombinasi sesuai subject 42 bonus.
 *
 * Aturan:
 * - Selalu prefix "0x"
 * - Flag '-' untuk left-justify (padding kanan)
 * - Width untuk minimal lebar output (padding spasi)
 * - Precision untuk minimal digit angka (padding 0 di depan angka)
 * - Jika precision 0 dan ptr NULL, hanya print "0x"
 */

// Fungsi untuk print karakter c sebanyak n kali (untuk padding)
static int putnchar(char c, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++)
        count += write(1, &c, 1);
    return count;
}

// Fungsi untuk menghitung panjang heksadesimal pointer
static int hexlen_ptr(uintptr_t n) {
    int len = 1;
    while (n /= 16)
        len++;
    return len;
}

// Fungsi untuk print pointer dalam heksadesimal (rekursif)
static int puthex_ptr(uintptr_t n) {
    int len = 0;
    char *base = "0123456789abcdef";
    if (n >= 16)
        len += puthex_ptr(n / 16);
    len += write(1, &base[n % 16], 1);
    return len;
}

// Fungsi utama print %p versi bonus
int print_p_bonus(void *ptr, t_fmt *fmt) {
    uintptr_t n = (uintptr_t)ptr;
    int numlen = (ptr == NULL && fmt->precision_specified && fmt->precision == 0) ? 0 : hexlen_ptr(n);
    int prefix = 2; // "0x"
    int prec_pad = (fmt->precision_specified && fmt->precision > numlen) ? fmt->precision - numlen : 0;
    int content_len = numlen + prec_pad + prefix;
    int width_pad = (fmt->width > content_len) ? fmt->width - content_len : 0;
    int total = 0;

    // Padding kiri (jika tidak minus)
    if (!fmt->flag_minus)
        total += putnchar(' ', width_pad);
    // Prefix 0x
    total += write(1, "0x", 2);
    // Precision padding
    total += putnchar('0', prec_pad);
    // Angka (hanya jika ptr != NULL atau precision != 0)
    if (!(ptr == NULL && fmt->precision_specified && fmt->precision == 0))
        total += puthex_ptr(n);
    // Padding kanan (jika minus)
    if (fmt->flag_minus)
        total += putnchar(' ', width_pad);
    return total;
} 