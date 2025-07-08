#include "ft_printf_bonus.h"
#include <stddef.h>

/*
 * ft_print_percent_bonus.c
 *
 * Fungsi print_percent_bonus mencetak karakter '%' (%%) dengan dukungan flag -, 0, width,
 * dan kombinasi sesuai subject 42 bonus.
 *
 * Aturan:
 * - Flag '-' untuk left-justify (padding kanan)
 * - Flag '0' untuk zero-padding (tanpa minus)
 * - Width untuk minimal lebar output (padding spasi/0)
 */

// Fungsi untuk print karakter c sebanyak n kali (untuk padding)
static int putnchar(char c, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++)
        count += write(1, &c, 1);
    return count;
}

// Fungsi utama print %% versi bonus
int print_percent_bonus(t_fmt *fmt) {
    int pad = (fmt->width > 1) ? fmt->width - 1 : 0;
    int total = 0;
    char padchar = (fmt->flag_zero && !fmt->flag_minus) ? '0' : ' ';
    // Padding kiri (jika tidak minus)
    if (!fmt->flag_minus)
        total += putnchar(padchar, pad);
    // Print karakter %
    total += write(1, "%", 1);
    // Padding kanan (jika minus)
    if (fmt->flag_minus)
        total += putnchar(' ', pad);
    return total;
} 