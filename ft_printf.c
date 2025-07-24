/* ************************************************************************** */
/*                                                                            */
/*   File utama: ft_printf.c                                                   */
/*   Berisi implementasi utama fungsi ft_printf mirip printf asli di C         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Fungsi untuk menangani format spesifik setelah menemukan karakter '%'
// Memproses flag, width, precision, dan tipe format
// format: pointer ke string format (akan digeser sesuai parsing)
// args:   daftar argumen variadik
// count:  pointer ke jumlah total karakter yang sudah dicetak
int	handle_format_specifier(const char **format, va_list args, int *count)
{
	int			temp;      // Menyimpan jumlah karakter yang dicetak oleh handler
	t_format	fmt;      // Struct untuk menyimpan hasil parsing format

	// Jika setelah '%' adalah '%' lagi, artinya ingin mencetak karakter '%'
	if (*(*format + 1) == '%')
	{
		// Cetak karakter '%', jika gagal (write return -1) maka error
		if (write(1, "%", 1) == -1)
			return (-1);
		// Tambah jumlah karakter yang dicetak
		(*count)++;
		// Geser pointer format sebanyak 2 (lewati '%%')
		*format += 2;
		return (0);
	}
	// Jika bukan '%%', berarti parsing format berikutnya
	(*format)++; // Lewati karakter '%'
	// Parsing flag, width, precision, dan tipe format
	fmt = ft_parse_format(format, args);
	// Dispatch ke handler sesuai tipe (c, s, d, x, dll)
	temp = ft_handle_format(args, fmt);
	// Jika handler gagal, return error
	if (temp == -1)
		return (-1);
	// Tambah jumlah karakter yang dicetak oleh handler
	*count += temp;
	return (0);
}

// Fungsi utama ft_printf: menerima format string dan argumen variadik
// format: string format seperti printf
// ...:    argumen variadik
// return: jumlah karakter yang dicetak, atau -1 jika error
int	ft_printf(const char *format, ...)
{
	va_list	args;   // Variabel untuk mengakses argumen variadik
	int		count;  // Menyimpan jumlah total karakter yang dicetak

	// Jika format NULL, langsung error
	if (format == NULL)
		return (-1);
	// Inisialisasi args untuk membaca argumen variadik
	va_start(args, format);
	count = 0; // Awal: belum ada karakter yang dicetak
	// Loop selama masih ada karakter di format string
	while (*format != '\0')
	{
		// Jika menemukan '%', berarti ada format spesifik
		if (*format == '%')
		{
			// Proses format spesifik, jika error return -1
			if (handle_format_specifier(&format, args, &count) == -1)
				return (-1);
		}
		else
		{
			// Jika bukan '%', cetak karakter biasa
			if (write(1, format, 1) == -1)
				return (-1);
			count++;    // Tambah jumlah karakter yang dicetak
			format++;   // Geser ke karakter berikutnya
		}
	}
	// Selesai, tutup akses argumen variadik
	va_end(args);
	// Kembalikan jumlah karakter yang dicetak
	return (count);
}

// Fungsi dispatcher: memilih fungsi cetak sesuai tipe format
// args: daftar argumen variadik
// fmt:  hasil parsing format (flag, width, precision, tipe)
// return: jumlah karakter yang dicetak oleh handler tipe
int	ft_handle_format(va_list args, t_format fmt)
{
	// Jika tipe 'c', ambil argumen int dan cetak sebagai karakter
	if (fmt.type == 'c')
		return (ft_print_char(fmt, va_arg(args, int)));
	// Jika tipe 's', ambil argumen char* dan cetak sebagai string
	else if (fmt.type == 's')
		return (ft_print_string(fmt, va_arg(args, char *)));
	// Jika tipe 'p', ambil argumen unsigned long dan cetak sebagai pointer
	else if (fmt.type == 'p')
		return (ft_print_pointer(fmt, va_arg(args, unsigned long)));
	// Jika tipe 'd' atau 'i', ambil argumen int dan cetak sebagai integer signed
	else if (fmt.type == 'd' || fmt.type == 'i')
		return (ft_print_int(fmt, va_arg(args, int)));
	// Jika tipe 'u', ambil argumen unsigned int dan cetak sebagai unsigned
	else if (fmt.type == 'u')
		return (ft_print_unsigned(fmt, va_arg(args, unsigned int)));
	// Jika tipe 'x', ambil argumen unsigned int dan cetak sebagai hex lowercase
	else if (fmt.type == 'x')
		return (ft_print_hex(fmt, va_arg(args, unsigned int)));
	// Jika tipe 'X', ambil argumen unsigned int dan cetak sebagai hex uppercase
	else if (fmt.type == 'X')
		return (ft_print_hex(fmt, va_arg(args, unsigned int)));
	// Jika tipe '%', cetak karakter '%'
	else if (fmt.type == '%')
		return (ft_print_percent(fmt));
	// Jika tipe tidak dikenali, tidak cetak apa-apa
	else
		return (0);
}
