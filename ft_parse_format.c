/* ************************************************************************** */
/*                                                                            */
/*   File: ft_parse_format.c                                                   */
/*   Berisi fungsi untuk parsing flag, width, precision, dan tipe format       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Inisialisasi struct t_format dengan nilai default untuk semua flag dan field
static t_format	ft_init_format(void)
{
	t_format	fmt; // Struct hasil parsing

	fmt.minus = 0;      // Tidak ada flag '-'
	fmt.zero = 0;       // Tidak ada flag '0'
	fmt.width = 0;      // Default width 0
	fmt.precision = -1; // Default: tidak ada precision
	fmt.dot = 0;        // Belum ada '.'
	fmt.hash = 0;       // Tidak ada flag '#'
	fmt.space = 0;      // Tidak ada flag ' '
	fmt.plus = 0;       // Tidak ada flag '+'
	fmt.type = 0;       // Tipe belum diisi
	return (fmt);
}

// Parsing flag seperti '-', '0', '#', '+', dan ' '
// Akan menggeser pointer format selama masih menemukan flag
static void	ft_parse_flags(const char **format, t_format *fmt)
{
	while (**format == '-' || **format == '0' || **format == '#'
		|| **format == '+' || **format == ' ')
	{
		if (**format == '-')
			fmt->minus = 1; // Set flag minus
		else if (**format == '0')
			fmt->zero = 1;  // Set flag zero
		else if (**format == '#')
			fmt->hash = 1;  // Set flag hash
		else if (**format == '+')
			fmt->plus = 1;  // Set flag plus
		else if (**format == ' ')
			fmt->space = 1; // Set flag spasi
		(*format)++;      // Geser ke karakter berikutnya
	}
}

// Parsing width, bisa berupa angka langsung atau '*'
// Jika '*', width diambil dari argumen variadik
static void	ft_parse_width(const char **format, t_format *fmt, va_list args)
{
	if (**format == '*')
	{
		fmt->width = va_arg(args, int); // Ambil width dari argumen
		if (fmt->width < 0)
		{
			fmt->minus = 1; // Width negatif artinya left-justify
			fmt->width = -fmt->width; // Ubah ke positif
		}
		(*format)++; // Geser pointer format
	}
	else
	{
		fmt->width = 0; // Default width
		// Selama karakter angka, parsing width manual
		while (ft_isdigit(**format))
		{
			fmt->width = fmt->width * 10 + (**format - '0'); // Tambah digit
			(*format)++;
		}
	}
}

// Parsing precision, diawali dengan '.' lalu angka atau '*'
// Jika '*', precision diambil dari argumen variadik
static void	ft_parse_precision(const char **format, t_format *fmt, va_list args)
{
	if (**format == '.')
	{
		(*format)++;      // Lewati '.'
		fmt->dot = 1;     // Tandai ada dot
		fmt->precision = 0; // Default precision 0
		if (**format == '*')
		{
			fmt->precision = va_arg(args, int); // Precision dari argumen
			(*format)++; // Geser pointer format
		}
		else
		{
			// Parsing digit precision manual
			while (ft_isdigit(**format))
			{
				fmt->precision = fmt->precision * 10 + (**format - '0');
				(*format)++;
			}
		}
	}
}

// Fungsi utama untuk parsing seluruh format setelah '%'
// Akan menggeser pointer format hingga ke tipe (c, s, d, x, dll)
t_format	ft_parse_format(const char **format, va_list args)
{
	t_format	fmt; // Struct hasil parsing

	fmt = ft_init_format(); // Inisialisasi default
	ft_parse_flags(format, &fmt); // Parsing flag
	ft_parse_width(format, &fmt, args); // Parsing width
	ft_parse_precision(format, &fmt, args); // Parsing precision
	fmt.type = **format; // Ambil tipe format (c, s, d, dll)
	(*format)++; // Geser pointer format
	return (fmt);
}
