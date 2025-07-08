#include "ft_printf.h"

// Fungsi utama untuk testing ft_printf
int main() {
    int a = 42;
    char *str = "World";
    void *ptr = &a;

    // Contoh penggunaan berbagai format
    ft_printf("Hello %%s!\n", str); // Menampilkan string
    ft_printf("Number: %%d, Hex: %%x, Char: %%c\n", a, a, 'A'); // Integer, Hex, Char
    ft_printf("Pointer: %%p\n", ptr); // Menampilkan pointer (alamat memori)
    ft_printf("Unsigned: %%u\n", 3000000000U); // Menampilkan unsigned integer
    ft_printf("Upper Hex: %%X\n", 255); // Menampilkan hex huruf besar
    ft_printf("Percent sign: %%\n"); // Menampilkan karakter '%'
    return 0;
} 