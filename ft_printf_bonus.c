<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:09:32 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/16 11:09:39 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
=======
#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>
>>>>>>> e2dce9b4dcee1cd0128f795096f2343fd9678027

int ft_printf_bonus(const char *format, ...) {
    va_list args;
    int i = 0;
    int count = 0;
<<<<<<< HEAD

=======
    
>>>>>>> e2dce9b4dcee1cd0128f795096f2343fd9678027
    va_start(args, format);

    while (format[i]) {
        if (format[i] == '%') {
            // Inisialisasi flag dan parameter format
            int minus = 0;
            int zero = 0;
            int width = 0;
            int dot = 0;
            int prec = -1;
            int plus = 0;
            int space = 0;
            int hash = 0;

            i++; // Lewati '%'
            // Parsing semua flag dan parameter format
            parse_flags(format, &i, &minus, &zero, &width, &dot, &prec, &plus, &space, &hash, args);

            // Format spesifier: 'd' atau 'i' untuk angka desimal
            if (format[i] == 'd' || format[i] == 'i') {
                int space_flag = 0;
                if (!plus) {
                    space_flag = space;
                }
                count += print_d(va_arg(args, int), width, minus, zero, prec, dot, plus, space_flag);
            }
            // Format spesifier: 's' untuk string
            else if (format[i] == 's') {
                count += print_s(va_arg(args, char *), width, minus, prec, dot);
            }
            // Format spesifier: 'x' untuk hex lowercase
            else if (format[i] == 'x') {
                count += print_x(va_arg(args, unsigned int), width, minus, zero, prec, dot, hash, 0);
            }
            // Format spesifier: 'X' untuk hex uppercase
            else if (format[i] == 'X') {
                count += print_x(va_arg(args, unsigned int), width, minus, zero, prec, dot, hash, 1);
            }
            // Format spesifier: '%%' untuk print karakter '%'
            else if (format[i] == '%') {
                count += ft_putchar('%');
            }
        } else {
            // Jika bukan '%', cetak karakter biasa
            count += ft_putchar(format[i]);
        }
        i++; // Lanjut ke karakter berikutnya
    }

    va_end(args);
    return count;
}
