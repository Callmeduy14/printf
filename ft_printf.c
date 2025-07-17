#include "ft_printf.h"

/*
** Fungsi utama ft_printf
** Menerima string format dan argumen variadic
** Mengembalikan jumlah karakter yang dicetak
*/
int ft_printf(const char *format, ...)
{
    va_list     args;   // Variadic argument list
    int         count;  // Jumlah total karakter yang dicetak
    int         temp;   // Jumlah karakter yang dicetak untuk satu format
    t_format    fmt;    // Struct untuk menyimpan info format

    // Jika format NULL, return error
    if (format == NULL)
        return (-1);
    
    va_start(args, format); // Inisialisasi variadic argument
    count = 0;
    
    // Loop setiap karakter dalam format string
    while (*format != '\0')
    {
        // Jika menemukan '%', berarti ada format spesifier
        if (*format == '%')
        {
            format++; // Lewati karakter '%'
            fmt = ft_parse_format(&format, args); // Parse flag, width, precision, type
            temp = ft_handle_format(&format, args, fmt); // Cetak sesuai type
            if (temp == -1)
                return (-1); // Jika error, return error
            count += temp; // Tambah jumlah karakter yang dicetak
        }
        else
        {
            // Jika bukan '%', cetak karakter biasa
            if (write(1, format, 1) == -1)
                return (-1);
            count++;
            format++;
        }
    }
    
    va_end(args); // Akhiri variadic argument
    return (count);
}

/*
** Menangani spesifier format
** Menerima pointer ke format, argumen variadic, dan struct format
** Mengembalikan jumlah karakter yang dicetak
*/
int ft_handle_format(const char **format, va_list args, t_format fmt)
{
    (void)format; // Tidak digunakan, hanya untuk konsistensi
    // Pilih fungsi print sesuai type
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