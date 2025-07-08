#include "ft_printf_bonus.h"
#include <stddef.h>

/*
 * ft_print_c_bonus.c
 *
 * Fungsi print_c_bonus mencetak karakter (%c) dengan dukungan flag -, width,
 * dan kombinasi sesuai subject 42 bonus.
 *
 * Aturan:
 * - Flag '-' untuk left-justify (padding kanan)
 * - Width untuk minimal lebar output (padding spasi)
 */

// Fungsi untuk print karakter c sebanyak n kali (untuk padding)
static int putnchar(char c, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++)
        count += write(1, &c, 1);
    return count;
}

// Fungsi utama print %c versi bonus
int print_c_bonus(char c, t_fmt *fmt) {
    int pad = (fmt->width > 1) ? fmt->width - 1 : 0;
    int total = 0;
    // Padding kiri (jika tidak minus)
    if (!fmt->flag_minus)
        total += putnchar(' ', pad);
    // Print karakter
    total += write(1, &c, 1);
    // Padding kanan (jika minus)
    if (fmt->flag_minus)
        total += putnchar(' ', pad);
    return total;
} 