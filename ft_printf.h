/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:30:49 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 20:30:50 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>    // Untuk write()
# include <stdarg.h>    // Untuk va_list
# include <stdlib.h>    // Untuk malloc() dan free()
# include "libft/libft.h" // Library buatan sendiri

# if defined (__linux__)
#  define PTRNULL "(nil)" // String NULL pointer di Linux
#  define NPTRSIZE 5      // Panjang string NULL pointer Linux
# elif defined (__APPLE__)
#  define PTRNULL "0x0"   // String NULL pointer di Mac
#  define NPTRSIZE 3      // Panjang string NULL pointer Mac
# endif

// Struktur untuk menyimpan informasi format
typedef struct s_format
{
	int		minus;      // Flag '-'
	int		zero;       // Flag '0'
	int		width;      // Minimum width
	int		precision;  // Precision
	int		dot;        // Flag '.' (ada precision)
	int		hash;       // Flag '#'
	int		space;      // Flag ' ' (spasi)
	int		plus;       // Flag '+'
	char	type;       // Tipe konversi (c, s, p, d, i, u, x, X, %)
} t_format;

// Struktur bantu untuk integer/hex
typedef struct s_intvars {
	int		is_neg;     // Apakah negatif
	int		len;        // Panjang digit
	int		print_sign; // Perlu cetak tanda
	int		pad_zero;   // Jumlah padding nol
	int		pad_space;  // Jumlah padding spasi
	char	pad_char;   // Karakter padding
	int		pos;        // Posisi buffer
} t_intvars;

// Prototipe fungsi utama
int		ft_printf(const char *format, ...); // Fungsi utama printf
int		ft_printf_bonus(const char *format, ...); // Versi bonus

// Fungsi parser dan handler
t_format	ft_parse_format(const char **format, va_list args); // Parsing format
int		ft_handle_format(va_list args, t_format fmt); // Handler format

// Fungsi pencetakan dengan format
int		ft_print_char(t_format fmt, int c); // Cetak karakter
int		ft_print_string(t_format fmt, char *str); // Cetak string
int		ft_print_pointer(t_format fmt, unsigned long ptr); // Cetak pointer
int		ft_print_int(t_format fmt, int n); // Cetak integer
int		ft_print_unsigned(t_format fmt, unsigned int n); // Cetak unsigned
int		ft_print_hex(t_format fmt, unsigned int n); // Cetak hex
int		ft_print_percent(t_format fmt); // Cetak '%'
int		ft_print_pointer_hex(unsigned long n); // Cetak pointer hex (opsional)

// Fungsi utilitas konversi
char	*ft_utoa(unsigned int n); // Unsigned ke string
char	*ft_xtoa(unsigned long n, int uppercase); // Unsigned ke hex string
int		ft_handle_width(t_format fmt, int len, int zero); // Handle width (opsional)

#endif
