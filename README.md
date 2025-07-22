# ft_printf

`ft_printf` adalah implementasi custom dari fungsi `printf` di bahasa C, yang mendukung berbagai format output seperti karakter, string, integer, unsigned, hexadecimal, pointer, dan beberapa flag tambahan (bonus).

## Fitur Utama
- Mendukung format: `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, `%%`
- Mendukung flag: `-`, `0`, `#`, `+`, ` ` (spasi), width, precision
- Kompatibel dengan Linux dan MacOS
- Tidak menggunakan fungsi printf asli dari C

## Struktur File
- `ft_printf.c`         : Fungsi utama printf dan handler format
- `ft_parse_format.c`   : Parsing flag, width, precision, dan tipe format
- `ft_printf_char.c`    : Cetak karakter
- `ft_printf_string.c`  : Cetak string
- `ft_printf_integer.c` : Cetak integer (signed)
- `ft_printf_unsigned.c`: Cetak unsigned integer
- `ft_printf_hex.c`     : Cetak hexadecimal
- `ft_printf_pointer.c` : Cetak pointer
- `ft_printf_percent.c` : Cetak karakter '%'
- `ft_conversion_utils.c`: Fungsi utilitas konversi angka ke string
- `ft_printf_bonus.c`   : Implementasi bonus flag
- `ft_printf.h`         : Header utama dan definisi struktur
- `libft/`              : Library fungsi-fungsi dasar (sendiri)
- `test_ft_printf.c`    : Contoh dan pengujian fungsi
- `Makefile`            : Untuk kompilasi otomatis

## Cara Kompilasi
Jalankan perintah berikut di terminal:

```
make
```

Untuk membersihkan file objek:
```
make clean
```

## Cara Menggunakan
Setelah kompilasi, Anda bisa menggunakan fungsi `ft_printf` di program C Anda:

```c
#include "ft_printf.h"

int main() {
    ft_printf("Halo %%s! Nilai: %d\n", "Dunia", 42);
    return 0;
}
```

## Pengujian
Jalankan file `test_ft_printf.c` untuk melihat perbandingan hasil dengan `printf` asli.

---

Proyek ini dibuat untuk latihan dan pembelajaran implementasi fungsi format output di bahasa C. 