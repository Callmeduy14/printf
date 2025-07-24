/* ************************************************************************** */
/*                                                                            */
/*   File: ft_variables.c                                                      */
/*   Berisi fungsi inisialisasi variabel bantu untuk integer dan hex           */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Inisialisasi variabel bantu untuk integer (signed)
void	init_int_vars(int n, t_format fmt, t_intvars *v, char *num)
{
	v->is_neg = (n < 0); // Apakah negatif
	v->len = ft_strlen(num);
	if (v->is_neg)
		v->len--; // Tidak hitung tanda minus
	if (fmt.dot && fmt.precision == 0 && n == 0)
		v->len = 0; // Edge case: zero precision
	v->pad_zero = 0;
	if (fmt.dot && fmt.precision > v->len)
		v->pad_zero = fmt.precision - v->len; // Padding nol
	v->print_sign = (v->is_neg || fmt.plus || fmt.space); // Perlu tanda?
	v->pad_space = 0;
	if (fmt.width > (v->print_sign + v->pad_zero + v->len))
		v->pad_space = fmt.width - (v->print_sign + v->pad_zero + v->len); // Padding spasi
	v->pad_char = ' ';
	if (fmt.zero && !fmt.minus && !fmt.dot)
		v->pad_char = '0'; // Padding nol jika flag zero
	v->pos = 0;
}

// Inisialisasi variabel bantu untuk hex
void	init_hex_vars(t_format *fmt, unsigned int n,
	t_intvars *v, char **hex)
{
	v->is_neg = 0;
	v->print_sign = 0;
	*hex = ft_xtoa(n, (fmt->type == 'X')); // Konversi ke string hex
	if (!*hex)
		return ;
	v->len = ft_strlen(*hex);
	if (fmt->dot && fmt->precision == 0 && n == 0)
		v->len = 0; // Edge case: zero precision
	v->pad_zero = 0;
	if (fmt->dot && fmt->precision > v->len)
		v->pad_zero = fmt->precision - v->len; // Padding nol
	v->pad_char = ' ';
	if (fmt->zero && !fmt->minus && !fmt->dot)
		v->pad_char = '0'; // Padding nol jika flag zero
}
