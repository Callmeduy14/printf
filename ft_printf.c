#include "ft_printf.h"

// Fungsi untuk menangani format spesifier setelah '%'
int handle_format_specifier(const char **format, va_list args, int *count)
{
    int     temp;         // Return sementara
    t_format fmt;         // Struktur format

    if (*(*format + 1) == '%') // Jika ada '%%', cetak satu '%'
    {
        if (write(1, "%", 1) == -1)
            return (-1);
        (*count)++;      // Tambah jumlah karakter
        *format += 2;    // Lewati dua karakter
        return (0);
    }
    (*format)++;         // Lewati '%'
    fmt = ft_parse_format(format, args); // Parse format spesifier
    temp = ft_handle_format(args, fmt);  // Cetak sesuai format
    if (temp == -1)
        return (-1);
    *count += temp;      // Tambah jumlah karakter
    return (0);
}

// Fungsi utama printf
int ft_printf(const char *format, ...)
{
    va_list args;    // Variadic argument list
    int     count;   // Jumlah karakter yang dicetak

    if (format == NULL)
        return (-1); // Jika format NULL, return error
    va_start(args, format); // Mulai membaca argumen variadic
    count = 0; // Inisialisasi counter
    while (*format != '\0') // Selama masih ada karakter di format string
    {
        if (*format == '%') // Jika menemukan '%', berarti ada format spesifier
        {
            if (handle_format_specifier(&format, args, &count) == -1)
                return (-1); // Jika error, return error
        }
        else
        {
            if (write(1, format, 1) == -1)
                return (-1); // Tulis karakter biasa
            count++;
            format++;
        }
    }
    va_end(args); // Selesai membaca argumen variadic
    return (count); // Return jumlah karakter yang dicetak
}

// Fungsi untuk memanggil handler sesuai tipe format
int	ft_handle_format(va_list args, t_format fmt)
{
	if (fmt.type == 'c')
		return (ft_print_char(fmt, va_arg(args, int))); // Cetak karakter
	else if (fmt.type == 's')
		return (ft_print_string(fmt, va_arg(args, char *))); // Cetak string
	else if (fmt.type == 'p')
		return (ft_print_pointer(fmt, va_arg(args, unsigned long))); // Cetak pointer
	else if (fmt.type == 'd' || fmt.type == 'i')
		return (ft_print_int(fmt, va_arg(args, int))); // Cetak integer
	else if (fmt.type == 'u')
		return (ft_print_unsigned(fmt, va_arg(args, unsigned int))); // Cetak unsigned
	else if (fmt.type == 'x')
		return (ft_print_hex(fmt, va_arg(args, unsigned int))); // Cetak hex kecil
	else if (fmt.type == 'X')
		return (ft_print_hex(fmt, va_arg(args, unsigned int))); // Cetak hex besar
	else if (fmt.type == '%')
		return (ft_print_percent(fmt)); // Cetak '%'
	else
		return (0); // Jika tipe tidak dikenali
}
