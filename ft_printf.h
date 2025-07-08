#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h> // Untuk menangani argumen variadik
#include <unistd.h> // Untuk fungsi write

// Deklarasi fungsi utama ft_printf
// Mirip dengan printf asli, menerima format string dan argumen variadik
int ft_printf(const char *format, ...);

#endif // FT_PRINTF_H 