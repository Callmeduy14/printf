/* ************************************************************************** */
/*                                                                            */
/*   File: ft_printf.h                                                         */
/*   Header utama untuk semua deklarasi fungsi, struct, dan macro ft_printf    */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "libft/libft.h"

// Macro untuk representasi NULL pointer pada Linux/Mac
# if defined(__linux__)
#  define PTRNULL "(nil)"
#  define NPTRSIZE 5
# elif defined(__APPLE__)
#  define PTRNULL "0x0"
#  define NPTRSIZE 3
# endif

// Struktur untuk menyimpan flag dan parameter format
typedef struct s_format
{
	int		minus;      // Flag '-'
	int		zero;       // Flag '0'
	int		width;      // Lebar minimal field
	int		precision;  // Presisi (jumlah digit/string)
	int		dot;        // Apakah ada '.'
	int		hash;       // Flag '#'
	int		space;      // Flag ' '
	int		plus;       // Flag '+'
	char	type;       // Tipe format (c, s, d, dll)
} t_format;

// Struktur variabel bantu untuk integer/hex
typedef struct s_intvars
{
	int			is_neg;      // Apakah negatif
	int			len;         // Panjang digit
	int			print_sign;  // Perlu tanda?
	int			pad_zero;    // Jumlah padding nol
	int			pad_space;   // Jumlah padding spasi
	char		pad_char;    // Karakter padding
	int			pos;         // Posisi buffer
	t_format	*fmt;        // Pointer ke format
	char		*hex;        // Buffer hex
} t_intvars;

// Deklarasi fungsi utama
int			ft_printf(const char *format, ...); // Fungsi utama printf
int			ft_printf_bonus(const char *format, ...); // Versi bonus

t_format	ft_parse_format(const char **format, va_list args); // Parsing format
int			ft_handle_format(va_list args, t_format fmt); // Dispatcher format

// Fungsi padding
void		handle_padding_int(int count, char c, char *buf, int *pos);
void		handle_padding_unsign(char *buffer, int *pos, int pad, char c);
int			calculate_unsigned_padding(t_format fmt, int len,
				unsigned int n, int *paddings);
int			calculate_hex_padding(t_format *fmt, t_intvars *v,
				unsigned int n);
int			calculate_string_padding(t_format fmt, int print_len);
int			write_padding(int count, char c);

// Inisialisasi variabel bantu
void		init_int_vars(int n, t_format fmt, t_intvars *v, char *num);
void		init_hex_vars(t_format *fmt, unsigned int n,
				t_intvars *v, char **hex);
int			write_hex_to_buffer(t_format *fmt, t_intvars *v,
				char *buffer, unsigned int n);
void		handle_sign_int(int n, t_format fmt, char *buf, int *pos);

// Fungsi cetak per tipe
int			ft_print_char(t_format fmt, int c);
int			ft_print_string(t_format fmt, char *str);
int			ft_print_pointer(t_format fmt, unsigned long ptr);
int			ft_print_int(t_format fmt, int n);
int			ft_print_unsigned(t_format fmt, unsigned int n);
int			ft_print_hex(t_format fmt, unsigned int n);
int			ft_print_percent(t_format fmt);
int			ft_print_pointer_hex(unsigned long n);

// Fungsi utilitas konversi
char		*ft_utoa(unsigned int n); // Unsigned ke string
char		*ft_xtoa(unsigned long n, int uppercase); // Unsigned ke hex string

#endif
