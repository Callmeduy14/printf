#include "ft_printf_bonus.h"
#include <stdlib.h>

/*
 * ft_print_d_bonus.c
 *
 * Fungsi print_d_bonus mencetak integer signed (%d/%i) dengan dukungan flag -, 0, +, spasi,
 * width, precision, dan kombinasi sesuai subject 42 bonus.
 *
 * Aturan:
 * - Flag '-' untuk left-justify (padding kanan)
 * - Flag '0' untuk zero-padding (hanya jika tidak ada precision dan tidak ada '-')
 * - Flag '+' untuk selalu tampilkan tanda plus jika positif
 * - Flag ' ' (spasi) untuk spasi di depan angka positif jika tidak ada tanda
 * - Width untuk minimal lebar output (padding spasi/0)
 * - Precision untuk minimal digit angka (padding 0 di depan angka)
 * - Jika precision 0 dan n 0, tidak print apapun untuk angka
 */

// Fungsi untuk menghitung panjang integer (tanpa tanda)
static int intlen(int n) {
    int len = 1;
    while (n /= 10)
        len++;
    return len;
}

// Fungsi untuk print karakter c sebanyak n kali (untuk padding)
static int putnchar(char c, int n) {
    int i, count = 0;
    for (i = 0; i < n; i++)
        count += write(1, &c, 1);
    return count;
}

// Fungsi untuk print integer dengan precision (tanpa tanda)
static int putnbr_prec(int n, int prec) {
    int len = 0, numlen = intlen(n);
    // Padding 0 untuk precision
    for (int i = 0; i < prec - numlen; i++)
        len += write(1, "0", 1);
    // Jika n == 0 dan precision == 0, tidak print apapun
    if (n == 0 && prec == 0)
        return len;
    if (n >= 10)
        len += putnbr_prec(n / 10, 0);
    len += write(1, &"0123456789"[n % 10], 1);
    return len;
}

// Struct bantu untuk menyimpan state print %d
// (memudahkan perhitungan padding, tanda, dsb)
typedef struct s_printd {
    int n;
    int is_neg;
    int numlen;
    int prec_pad;
    int width_pad;
    int total;
} t_printd;

// Fungsi utama print %d versi bonus
int print_d_bonus(int n, t_fmt *fmt) {
    t_printd pd;
    pd.n = n;
    pd.is_neg = (n < 0);
    pd.numlen = intlen(n < 0 ? -n : n);
    if (n == 0 && fmt->precision_specified && fmt->precision == 0)
        pd.numlen = 0; // Tidak print apapun jika precision 0 dan n 0
    pd.prec_pad = (fmt->precision_specified && fmt->precision > pd.numlen) ? fmt->precision - pd.numlen : 0;
    int sign = pd.is_neg || fmt->flag_plus || fmt->flag_space;
    int content_len = pd.numlen + pd.prec_pad + (pd.is_neg || fmt->flag_plus || fmt->flag_space ? 1 : 0);
    pd.width_pad = (fmt->width > content_len) ? fmt->width - content_len : 0;
    pd.total = 0;

    // Padding kiri (spasi, jika tidak minus dan tidak zero)
    if (!fmt->flag_minus && (!fmt->flag_zero || fmt->precision_specified))
        pd.total += putnchar(' ', pd.width_pad);
    // Tanda
    if (pd.is_neg)
        pd.total += write(1, "-", 1);
    else if (fmt->flag_plus)
        pd.total += write(1, "+", 1);
    else if (fmt->flag_space)
        pd.total += write(1, " ", 1);
    // Zero padding (flag 0, tanpa precision, tanpa minus)
    if (!fmt->flag_minus && fmt->flag_zero && !fmt->precision_specified)
        pd.total += putnchar('0', pd.width_pad);
    // Precision padding
    pd.total += putnchar('0', pd.prec_pad);
    // Angka (hanya jika tidak 0 dan precision 0)
    if (!(n == 0 && fmt->precision_specified && fmt->precision == 0))
        pd.total += putnbr_prec(n < 0 ? -n : n, 0);
    // Padding kanan (jika minus)
    if (fmt->flag_minus)
        pd.total += putnchar(' ', pd.width_pad);
    return pd.total;
} 