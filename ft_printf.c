#include "ft_printf.h"

/*
** Fungsi utama ft_printf
** Menerima string format dan argumen variadic
** Mengembalikan jumlah karakter yang dicetak
*/
int ft_printf(const char *format, ...)
{
	va_list	 args;   // Variadic argument list untuk ambil argumen variabel
	int		 count;  // Jumlah total karakter yang sudah dicetak
	int		 temp;   // Jumlah karakter yang dicetak untuk satu format spesifik
	t_format	fmt;	// Struct untuk menyimpan info parsing format spesifier

	// Jika string format NULL, return error (-1)
	if (format == NULL)
		return (-1);

	va_start(args, format); // Mulai baca argumen variabel
	count = 0;

	// Loop sampai akhir string format
	while (*format != '\0')
	{
		// Jika ketemu '%%', ini harusnya cetak literal '%'
		if (*format == '%' && *(format + 1) == '%')
		{
			// Cetak satu karakter '%'
			if (write(1, "%", 1) == -1)
				return (-1);  // Error saat menulis ke stdout

			count++;	   // Tambah jumlah karakter yang dicetak
			format += 2;   // Lewati dua karakter '%' dalam format string
		}
		// Jika ketemu '%' tapi bukan '%%', berarti format specifier sesungguhnya
		else if (*format == '%')
		{
			format++;					  // Lewati karakter '%'
			fmt = ft_parse_format(&format, args);  // Parse flag, width, precision, type
			temp = ft_handle_format(args, fmt); // Cetak sesuai tipe format
			if (temp == -1)
				return (-1);			  // Jika error saat cetak, return error
			count += temp;				// Tambah jumlah karakter yang sudah dicetak
		}
		// Jika bukan karakter '%', cetak biasa
		else
		{
			if (write(1, format, 1)== -1)
				return (-1);			  // Error saat menulis ke stdout
			count++;					  // Tambah jumlah karakter yang sudah dicetak
			format++;					 // Geser ke karakter selanjutnya di format string
		}
	}
	va_end(args);   // Akhiri pembacaan argumen variabel
	return (count); // Return total karakter yang sudah dicetak
}


/*
** Menangani spesifier format
** Menerima pointer ke format, argumen variadic, dan struct format
** Mengembalikan jumlah karakter yang dicetak
*/
int ft_handle_format(va_list args, t_format fmt)
{
	if (fmt.type == 'c')
		return (ft_print_char(fmt, va_arg(args, int)));
	else if (fmt.type == 's')
		return (ft_print_string(fmt, va_arg(args, char *)));
	else if (fmt.type == 'p')
		return (ft_print_pointer(fmt, va_arg(args, unsigned long)));
	else if (fmt.type == 'd' || fmt.type == 'i')
		return (ft_print_int(fmt, va_arg(args, int)));
	else if (fmt.type == 'u')
		return (ft_print_unsigned(fmt, va_arg(args, unsigned int)));
	else if (fmt.type == 'x')
		return (ft_print_hex(fmt, va_arg(args, unsigned int), 0));
	else if (fmt.type == 'X')
		return (ft_print_hex(fmt, va_arg(args, unsigned int), 1));
	else if (fmt.type == '%')
		return (ft_print_percent(fmt));
	else
		return (0); // Jika type tidak dikenali, tidak cetak apa-apa
}
