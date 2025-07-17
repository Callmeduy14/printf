#include "ft_printf.h"

/*
** Mencetak karakter tunggal
** Return: jumlah karakter yang dicetak (1 jika sukses, -1 jika error)
*/
int ft_print_char(t_format fmt, int c)
{
    (void)fmt; // Tidak ada flag yang mempengaruhi %c
    // Tulis karakter ke stdout
    if (write(1, &c, 1) == -1)
        return (-1);
    return (1);
}

/*
** Mencetak string dengan flag width, precision, dan alignment
** Jika string NULL, cetak "(null)"
** Return: jumlah karakter yang dicetak
*/
int ft_print_string(t_format fmt, char *str)
{
    int count = 0; // Jumlah karakter yang dicetak
    int len = 0;   // Panjang string
    int print_len = 0; // Panjang substring yang akan dicetak
    const char *nullstr = "(null)";
    if (!str)
        str = (char *)nullstr; // Ganti NULL dengan (null)
    while (str[len])
        len++;
    print_len = len;
    // Jika ada precision, batasi panjang string
    if (fmt.dot == 1 && fmt.precision < print_len && fmt.precision >= 0)
        print_len = fmt.precision;
    int pad_space = fmt.width - print_len;
    if (pad_space < 0)
        pad_space = 0;
    // Padding kiri jika right-aligned
    if (fmt.minus == 0 && pad_space > 0)
    {
        while (pad_space > 0)
        {
            if (write(1, " ", 1) == -1)
                return -1;
            count++;
            pad_space--;
        }
    }
    // Cetak substring
    if (print_len > 0)
    {
        if (write(1, str, print_len) == -1)
            return -1;
        count += print_len;
    }
    // Padding kanan jika left-aligned
    if (fmt.minus == 1)
    {
        pad_space = fmt.width - count;
        while (pad_space > 0)
        {
            if (write(1, " ", 1) == -1)
                return -1;
            count++;
            pad_space--;
        }
    }
    return count;
}

/*
** Mencetak pointer dalam format hexadecimal, diawali dengan "0x"
** Return: jumlah karakter yang dicetak
*/
int ft_print_pointer(t_format fmt, unsigned long ptr)
{
    int count;
    // Cetak prefix "0x"
    if (write(1, "0x", 2) == -1)
        return (-1);
    count = 2;
    // Cetak nilai pointer dalam hex (menggunakan ft_print_hex)
    count += ft_print_hex(fmt, ptr, 0);
    return (count);
}

/*
** Mencetak integer (desimal) dengan semua flag, width, precision, dan alignment
** Return: jumlah karakter yang dicetak
*/
int ft_print_int(t_format fmt, int n)
{
    char *num;
    int count = 0;      // Jumlah karakter yang dicetak
    int len = 0;        // Panjang digit (tanpa sign)
    int is_neg = 0;     // Apakah n negatif
    int pad_zero = 0;   // Jumlah zero padding (precision)
    int print_sign = 0; // Apakah perlu cetak tanda (+, -, spasi)
    int i;
    // Cek negatif
    if (n < 0)
        is_neg = 1;
    num = ft_itoa(n); // Konversi ke string
    if (!num)
        return -1;
    // Hitung panjang digit (tanpa sign)
    i = 0;
    while (num[i])
        i++;
    len = i;
    if (is_neg)
        len--;
    // Precision 0 dan n==0: tidak cetak digit
    if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
        len = 0;
    // Hitung zero padding (precision)
    if (fmt.dot == 1 && fmt.precision > len)
        pad_zero = fmt.precision - len;
    // Apakah perlu cetak tanda
    if (is_neg || fmt.plus || fmt.space)
        print_sign = 1;
    // Hitung total karakter yang akan dicetak (sign + zero + digit)
    int total = print_sign + pad_zero + len;
    if (len == 0)
        total = print_sign;
    // Hitung padding spasi
    int pad_space = fmt.width - total;
    if (pad_space < 0)
        pad_space = 0;
    // Cetak padding kiri jika right-aligned
    if (!fmt.minus) {
        char pad = ' ';
        if (fmt.zero && fmt.dot == 0) pad = '0';
        while (pad_space > 0) {
            if (write(1, &pad, 1) == -1) { free(num); return -1; }
            count++;
            pad_space--;
        }
    }
    // Cetak tanda
    if (is_neg) {
        if (write(1, "-", 1) == -1) { free(num); return -1; }
        count++;
    } else if (fmt.plus) {
        if (write(1, "+", 1) == -1) { free(num); return -1; }
        count++;
    } else if (fmt.space) {
        if (write(1, " ", 1) == -1) { free(num); return -1; }
        count++;
    }
    // Cetak zero padding (precision)
    i = 0;
    while (pad_zero > 0) {
        if (write(1, "0", 1) == -1) { free(num); return -1; }
        count++;
        pad_zero--;
    }
    // Cetak digit (jika ada)
    if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0)) {
        i = is_neg;
        while (num[i]) {
            if (write(1, &num[i], 1) == -1) { free(num); return -1; }
            count++;
            i++;
        }
    }
    // Cetak padding kanan jika left-aligned
    if (fmt.minus) {
        int left_pad = fmt.width - count;
        while (left_pad > 0) {
            if (write(1, " ", 1) == -1) { free(num); return -1; }
            count++;
            left_pad--;
        }
    }
    free(num);
    return count;
}

/*
** Mencetak unsigned integer dengan flag width, precision, dan alignment
** Return: jumlah karakter yang dicetak
*/
int ft_print_unsigned(t_format fmt, unsigned int n)
{
    char *num;
    int count = 0;      // Jumlah karakter yang dicetak
    int len = 0;        // Panjang digit
    int pad_zero = 0;   // Jumlah zero padding (precision)
    int i;
    num = ft_utoa(n); // Konversi ke string
    if (!num)
        return -1;
    i = 0;
    while (num[i])
        i++;
    len = i;
    // Precision 0 dan n==0: tidak cetak digit
    if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
        len = 0;
    // Hitung zero padding (precision)
    if (fmt.dot == 1 && fmt.precision > len)
        pad_zero = fmt.precision - len;
    int total = pad_zero + len;
    if (len == 0)
        total = 0;
    int pad_space = fmt.width - total;
    if (pad_space < 0)
        pad_space = 0;
    // Cetak padding kiri jika right-aligned
    if (!fmt.minus) {
        char pad = ' ';
        if (fmt.zero && fmt.dot == 0) pad = '0';
        while (pad_space > 0) {
            if (write(1, &pad, 1) == -1) { free(num); return -1; }
            count++;
            pad_space--;
        }
    }
    // Cetak zero padding (precision)
    i = 0;
    while (pad_zero > 0) {
        if (write(1, "0", 1) == -1) { free(num); return -1; }
        count++;
        pad_zero--;
    }
    // Cetak digit (jika ada)
    if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0)) {
        i = 0;
        while (num[i]) {
            if (write(1, &num[i], 1) == -1) { free(num); return -1; }
            count++;
            i++;
        }
    }
    // Cetak padding kanan jika left-aligned
    if (fmt.minus) {
        int left_pad = fmt.width - count;
        while (left_pad > 0) {
            if (write(1, " ", 1) == -1) { free(num); return -1; }
            count++;
            left_pad--;
        }
    }
    free(num);
    return count;
}

/*
** Mencetak bilangan hexadecimal dengan flag #, width, precision, dan alignment
** uppercase: 1 untuk huruf besar, 0 untuk huruf kecil
** Return: jumlah karakter yang dicetak
*/
int ft_print_hex(t_format fmt, unsigned int n, int uppercase)
{
    char *hex;
    int count = 0;      // Jumlah karakter yang dicetak
    int len = 0;        // Panjang digit
    int pad_zero = 0;   // Jumlah zero padding (precision)
    int prefix = 0;     // Panjang prefix (0x/0X)
    int i;
    if (fmt.hash && n != 0)
        prefix = 2;
    hex = ft_xtoa(n, uppercase); // Konversi ke string hex
    if (!hex)
        return -1;
    i = 0;
    while (hex[i])
        i++;
    len = i;
    // Precision 0 dan n==0: tidak cetak digit
    if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
        len = 0;
    // Hitung zero padding (precision)
    if (fmt.dot == 1 && fmt.precision > len)
        pad_zero = fmt.precision - len;
    int total = prefix + pad_zero + len;
    if (len == 0)
        total = prefix;
    int pad_space = fmt.width - total;
    if (pad_space < 0)
        pad_space = 0;
    // Cetak padding kiri jika right-aligned
    if (!fmt.minus) {
        char pad = ' ';
        if (fmt.zero && fmt.dot == 0) pad = '0';
        while (pad_space > 0) {
            if (write(1, &pad, 1) == -1) { free(hex); return -1; }
            count++;
            pad_space--;
        }
    }
    // Cetak prefix 0x/0X jika perlu
    if (prefix) {
        if (uppercase) {
            if (write(1, "0X", 2) == -1) { free(hex); return -1; }
        } else {
            if (write(1, "0x", 2) == -1) { free(hex); return -1; }
        }
        count += 2;
    }
    // Cetak zero padding (precision)
    i = 0;
    while (pad_zero > 0) {
        if (write(1, "0", 1) == -1) { free(hex); return -1; }
        count++;
        pad_zero--;
    }
    // Cetak digit (jika ada)
    if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0)) {
        i = 0;
        while (hex[i]) {
            if (write(1, &hex[i], 1) == -1) { free(hex); return -1; }
            count++;
            i++;
        }
    }
    // Cetak padding kanan jika left-aligned
    if (fmt.minus) {
        int left_pad = fmt.width - count;
        while (left_pad > 0) {
            if (write(1, " ", 1) == -1) { free(hex); return -1; }
            count++;
            left_pad--;
        }
    }
    free(hex);
    return count;
}

/*
** Mencetak tanda persen (%)
** Return: jumlah karakter yang dicetak (1 jika sukses, -1 jika error)
*/
int ft_print_percent(t_format fmt)
{
    (void)fmt;
    if (write(1, "%", 1) == -1)
        return (-1);
    return (1);
}