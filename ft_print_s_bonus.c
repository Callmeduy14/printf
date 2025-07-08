#include "ft_printf_bonus.h"
#include <stddef.h>

/*
 * ft_print_s_bonus.c
 *
 * Fungsi print_s_bonus mencetak string (%s) dengan dukungan flag -, width, precision,
 * dan kombinasi sesuai subject 42 bonus.
 *
 * Aturan:
 * - Flag '-' untuk left-justify (padding kanan)
 * - Width untuk minimal lebar output (padding spasi)
 * - Precision untuk maksimal karakter yang dicetak dari string
 * - Jika string NULL, print (null)
 */

// Fungsi untuk print karakter c sebanyak n kali (untuk padding)
static int putnchar(char c, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++)
        count += write(1, &c, 1);
    return count;
}

// Fungsi utama print %s versi bonus
int print_s_bonus(const char *s, t_fmt *fmt) {
    int slen = 0, printlen, pad, total = 0;
    if (!s)
        s = "(null)";
    while (s[slen])
        slen++;
    // Jika ada precision, print maksimal precision karakter
    printlen = (fmt->precision_specified && fmt->precision < slen) ? fmt->precision : slen;
    pad = (fmt->width > printlen) ? fmt->width - printlen : 0;
    // Padding kiri (jika tidak minus)
    if (!fmt->flag_minus)
        total += putnchar(' ', pad);
    // Print string (maksimal printlen karakter)
    total += write(1, s, printlen);
    // Padding kanan (jika minus)
    if (fmt->flag_minus)
        total += putnchar(' ', pad);
    return total;
} 