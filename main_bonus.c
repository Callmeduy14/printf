#include "ft_printf_bonus.h"

/*
 * main_bonus.c
 *
 * File ini digunakan untuk menguji semua fitur bonus dari ft_printf.
 * Setiap blok menguji kombinasi flag, width, precision, dan semua specifier.
 * Komentar di setiap bagian menjelaskan apa yang diuji dan contoh output yang diharapkan.
 */

int main(void) {
    int n = 42;
    char *str = "Hello, 42!";
    void *ptr = str;

    // ======================
    // Test %d dan %i (signed integer)
    // ======================
    // Tanpa flag
    ft_printf("[%%d] |%d|\n", n); // |42|
    // Width
    ft_printf("[%%10d] |%10d|\n", n); // |        42|
    // Left-justify
    ft_printf("[%%-10d] |%-10d|\n", n); // |42        |
    // Zero-padding
    ft_printf("[%%010d] |%010d|\n", n); // |0000000042|
    // Plus sign
    ft_printf("[%%+10d] |%+10d|\n", n); // |       +42|
    // Space sign
    ft_printf("[%% 10d] |% 10d|\n", n); // |        42|
    // Precision
    ft_printf("[%%.5d] |%.5d|\n", n); // |00042|
    // Width + Precision
    ft_printf("[%%10.5d] |%10.5d|\n", n); // |     00042|
    // Left-justify + Precision
    ft_printf("[%%-10.5d] |%-10.5d|\n", n); // |00042     |
    // Plus + Zero-padding
    ft_printf("[%%+010d] |%+010d|\n", n); // |+000000042|

    // ======================
    // Test %u (unsigned integer)
    // ======================
    ft_printf("[%%u] |%u|\n", 3000000000U); // |3000000000|
    ft_printf("[%%10u] |%10u|\n", 3000000000U); // |3000000000|
    ft_printf("[%%-10u] |%-10u|\n", 3000000000U); // |3000000000|
    ft_printf("[%%010u] |%010u|\n", 3000000000U); // |3000000000|
    ft_printf("[%%.8u] |%.8u|\n", 300U); // |00000300|

    // ======================
    // Test %x dan %X (hexadecimal)
    // ======================
    ft_printf("[%%x] |%x|\n", 255); // |ff|
    ft_printf("[%%#x] |%#x|\n", 255); // |0xff|
    ft_printf("[%%10x] |%10x|\n", 255); // |        ff|
    ft_printf("[%%-10x] |%-10x|\n", 255); // |ff        |
    ft_printf("[%%010x] |%010x|\n", 255); // |00000000ff|
    ft_printf("[%%#010x] |%#010x|\n", 255); // |0x000000ff|
    ft_printf("[%%.4x] |%.4x|\n", 255); // |00ff|
    ft_printf("[%%10.4x] |%10.4x|\n", 255); // |      00ff|
    ft_printf("[%%X] |%X|\n", 255); // |FF|
    ft_printf("[%%#X] |%#X|\n", 255); // |0XFF|

    // ======================
    // Test %s (string)
    // ======================
    ft_printf("[%%s] |%s|\n", str); // |Hello, 42!|
    ft_printf("[%%10s] |%10s|\n", str); // | Hello, 42!|
    ft_printf("[%%-10s] |%-10s|\n", str); // |Hello, 42! |
    ft_printf("[%%.5s] |%.5s|\n", str); // |Hello|
    ft_printf("[%%10.5s] |%10.5s|\n", str); // |     Hello|
    ft_printf("[%%-10.5s] |%-10.5s|\n", str); // |Hello     |
    ft_printf("[%%s NULL] |%s|\n", (char *)0); // |(null)|

    // ======================
    // Test %c (char)
    // ======================
    ft_printf("[%%c] |%c|\n", 'A'); // |A|
    ft_printf("[%%5c] |%5c|\n", 'A'); // |    A|
    ft_printf("[%%-5c] |%-5c|\n", 'A'); // |A    |

    // ======================
    // Test %p (pointer)
    // ======================
    ft_printf("[%%p] |%p|\n", ptr); // |0x...|
    ft_printf("[%%20p] |%20p|\n", ptr); // |         0x...|
    ft_printf("[%%-20p] |%-20p|\n", ptr); // |0x...         |
    ft_printf("[%%.10p] |%.10p|\n", ptr); // |0x0000...|
    ft_printf("[%%20.10p] |%20.10p|\n", ptr); // |     0x0000...|
    ft_printf("[%%p NULL] |%p|\n", (void *)0); // |0x0|

    // ======================
    // Test %% (percent literal)
    // ======================
    ft_printf("[%%%%] |%%|\n"); // |%|
    ft_printf("[%%10%%] |%10%|\n"); // |         %|
    ft_printf("[%%-10%%] |%-10%|\n"); // |%         |
    ft_printf("[%%010%%] |%010%|\n"); // |000000000%|

    return 0;
} 