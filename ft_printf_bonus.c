#include "ft_printf_bonus.h"
#include <stdarg.h>

/*
 * ft_printf_bonus.c
 *
 * Fungsi utama ft_printf versi bonus.
 * Mendukung semua specifier wajib (%c, %s, %p, %d, %i, %u, %x, %X, %%)
 * serta flag -, 0, #, +, spasi, width, precision, dan kombinasi.
 *
 * Alur:
 * - Setiap kali menemukan '%', lakukan parsing flag, width, precision, dan specifier.
 * - Panggil fungsi print sesuai specifier, passing struct format hasil parsing.
 * - Untuk karakter biasa, langsung print.
 * - Return: jumlah karakter yang dicetak (seperti printf asli).
 */

// Deklarasi fungsi print untuk setiap specifier
int parse_format(const char *s, int i, t_fmt *fmt, va_list args);
int print_d_bonus(int n, t_fmt *fmt);
int print_s_bonus(const char *s, t_fmt *fmt);
int print_x_bonus(unsigned int n, t_fmt *fmt, int upper);
int print_u_bonus(unsigned int n, t_fmt *fmt);
int print_c_bonus(char c, t_fmt *fmt);
int print_p_bonus(void *ptr, t_fmt *fmt);
int print_percent_bonus(t_fmt *fmt);

typedef int (*t_print_func)(va_list *, t_fmt *);

// Wrapper untuk %d (bisa dikembangkan untuk %i)
static int print_d_wrapper(va_list *args, t_fmt *fmt) {
    int n = va_arg(*args, int);
    return print_d_bonus(n, fmt);
}

/*
 * Fungsi utama ft_printf versi bonus
 * - Melakukan loop pada format string
 * - Jika menemukan '%', parsing format dan panggil print sesuai specifier
 * - Jika karakter biasa, langsung print
 */
int ft_printf(const char *format, ...) {
    va_list args;
    int i = 0, len = 0;
    va_start(args, format);
    while (format[i]) {
        if (format[i] == '%') {
            t_fmt fmt = fmt_init();
            int next = parse_format(format, i + 1, &fmt, args);
            // Panggil print sesuai specifier
            if (fmt.specifier == 'd' || fmt.specifier == 'i') {
                len += print_d_wrapper(&args, &fmt);
            } else if (fmt.specifier == 's') {
                const char *str = va_arg(args, const char *);
                len += print_s_bonus(str, &fmt);
            } else if (fmt.specifier == 'x') {
                unsigned int n = va_arg(args, unsigned int);
                len += print_x_bonus(n, &fmt, 0);
            } else if (fmt.specifier == 'X') {
                unsigned int n = va_arg(args, unsigned int);
                len += print_x_bonus(n, &fmt, 1);
            } else if (fmt.specifier == 'u') {
                unsigned int n = va_arg(args, unsigned int);
                len += print_u_bonus(n, &fmt);
            } else if (fmt.specifier == 'c') {
                char c = (char)va_arg(args, int);
                len += print_c_bonus(c, &fmt);
            } else if (fmt.specifier == 'p') {
                void *ptr = va_arg(args, void *);
                len += print_p_bonus(ptr, &fmt);
            } else if (fmt.specifier == '%') {
                len += print_percent_bonus(&fmt);
            }
            // Tambahkan else jika ingin handle specifier lain
            i = next;
        } else {
            // Print karakter biasa
            len += write(1, &format[i], 1);
            i++;
        }
    }
    va_end(args);
    return len;
} 