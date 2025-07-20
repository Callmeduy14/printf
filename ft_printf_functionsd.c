#include "ft_printf.h"

/*
** Mencetak karakter tunggal
** Return: jumlah karakter yang dicetak (1 jika sukses, -1 jika error)
*/
int ft_print_char(t_format fmt, int c)
{
    int count = 0;
    int padding = 0;
    char ch = (char)c;
    int write_result;

    // Calculate padding spaces
    if (fmt.width > 1)
        padding = fmt.width - 1;

    // Right alignment (padding before character)
    if (!fmt.minus)
    {
        int i = 0;
        while (i < padding)
        {
            write_result = write(1, " ", 1);
            if (write_result == -1)
                return -1;
            count += write_result;
            i++;
        }
    }

    // Print the character
    write_result = write(1, &ch, 1);
    if (write_result == -1)
        return -1;
    count += write_result;

    // Left alignment (padding after character)
    if (fmt.minus)
    {
        int i = 0;
        while (i < padding)
        {
            write_result = write(1, " ", 1);
            if (write_result == -1)
                return -1;
            count += write_result;
            i++;
        }
    }

    return count;
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
int ft_print_pointer_hex(unsigned long n)
{
	char *str = ft_xtoa(n, 0);  // ubah ke hex lowercase
	int count = 0;

	if (!str)
		return -1;

	// pakai ft_strlen untuk hitung panjang string hex
	int len = (int)ft_strlen(str);

	// tulis string hex ke stdout
	if (write(1, str, len) == -1)
	{
		free(str);
		return -1;
	}
	count = len;
	free(str);
	return count;
}

int ft_print_pointer(t_format fmt, unsigned long ptr)
{
	int count = 0;  // Total karakter yang sudah dicetak
	int len;		// Panjang string hasil konversi pointer + prefix "0x"
	int pad;		// Banyaknya spasi untuk padding (jika width > panjang string)
	int i;		  // Variabel iterator untuk loop

	char *str;	  // String hasil konversi pointer ke hex (tanpa prefix "0x")

	// Jika pointer NULL (0), string yang dicetak hanya "0"
	if (ptr == 0)
		str = "0";
	else
	{
		// Jika bukan NULL, konversi pointer ke string hex lowercase
		str = ft_xtoa(ptr, 0);
		if (!str)   // Jika malloc gagal, return error
			return -1;
	}

	// Hitung panjang string hex + 2 karakter untuk "0x"
	len = (int)ft_strlen(str) + 2;

	pad = 0; // Inisialisasi padding spasi
	// Jika lebar field (width) lebih besar dari panjang string, hitung paddingnya
	if (fmt.width > len)
		pad = fmt.width - len;

	// Jika flag minus tidak aktif (artinya padding di kiri)
	if (!fmt.minus)
	{
		// Tulis spasi sebanyak pad ke stdout sebagai padding kiri
		for (i = 0; i < pad; i++)
		{
			if (write(1, " ", 1) == -1)
			{
				// Jika terjadi error saat menulis, free memori jika perlu lalu return error
				if (ptr != 0)
					free(str);
				return -1;
			}
			count++; // Tambah jumlah karakter yang dicetak
		}
	}

	// Tulis prefix "0x" untuk menunjukan bahwa ini pointer hex
	if (write(1, "0x", 2) == -1)
	{
		if (ptr != 0)
			free(str);
		return -1;
	}
	count += 2;

	// Tulis string hex pointer ke stdout
	if (write(1, str, ft_strlen(str)) == -1)
	{
		if (ptr != 0)
			free(str);
		return -1;
	}
	count += ft_strlen(str);

	// Jika flag minus aktif (padding di kanan), tulis spasi setelah string
	if (fmt.minus)
	{
		for (i = 0; i < pad; i++)
		{
			if (write(1, " ", 1) == -1)
			{
				if (ptr != 0)
					free(str);
				return -1;
			}
			count++;
		}
	}

	// Jika pointer bukan NULL, maka string hasil konversi dialokasikan di heap
	// Jadi harus di-free untuk menghindari memory leak
	if (ptr != 0)
		free(str);

	return count; // Kembalikan total karakter yang sudah dicetak
}

/*
** Mencetak integer (desimal) dengan semua flag, width, precision, dan alignment
** Return: jumlah karakter yang dicetak
*/

int ft_print_int(t_format fmt, int n)
{
    char *num;
    int count = 0;
    int write_result;
    int is_neg = (n < 0);
    int print_sign = (is_neg || fmt.plus || fmt.space);
    char *digits;

    num = ft_itoa(n);
    if (!num)
        return -1;

    digits = num;
    if (is_neg && num[0] == '-')
        digits = num + 1;

    int len = ft_strlen(digits);
    if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
        len = 0;

    // Calculate padding
    int pad_zero = (fmt.dot == 1 && fmt.precision > len) ? fmt.precision - len : 0;
    int total_len = print_sign + pad_zero + len;
    int pad_space = (fmt.width > total_len) ? fmt.width - total_len : 0;

    // Determine padding character
    char pad_char = (fmt.zero && !fmt.minus && !fmt.dot) ? '0' : ' ';

    // Right alignment (padding before content)
    if (!fmt.minus)
    {
        // Special case: print sign before zero padding
        if (pad_char == '0' && print_sign)
        {
            if (is_neg) write_result = write(1, "-", 1);
            else if (fmt.plus) write_result = write(1, "+", 1);
            else write_result = write(1, " ", 1);

            if (write_result == -1) { free(num); return -1; }
            count += write_result;
            print_sign = 0;
        }

        // Space padding
        while (pad_space-- > 0)
        {
            write_result = write(1, &pad_char, 1);
            if (write_result == -1) { free(num); return -1; }
            count += write_result;
        }
    }

    // Print sign if not printed yet
    if (print_sign)
    {
        if (is_neg) write_result = write(1, "-", 1);
        else if (fmt.plus) write_result = write(1, "+", 1);
        else write_result = write(1, " ", 1);

        if (write_result == -1) { free(num); return -1; }
        count += write_result;
    }

    // Zero padding from precision
    while (pad_zero-- > 0)
    {
        write_result = write(1, "0", 1);
        if (write_result == -1) { free(num); return -1; }
        count += write_result;
    }

    // Print digits (except when precision=0 and n=0)
    if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0))
    {
        int i = 0;
        while (digits[i])
        {
            write_result = write(1, &digits[i++], 1);
            if (write_result == -1) { free(num); return -1; }
            count += write_result;
        }
    }

    // Left alignment (padding after content)
    if (fmt.minus)
    {
        while (pad_space-- > 0)
        {
            write_result = write(1, " ", 1);
            if (write_result == -1) { free(num); return -1; }
            count += write_result;
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
	int count = 0;	  // Jumlah karakter yang dicetak
	int len = 0;		// Panjang digit
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
		char pad = ' ';
	if (fmt.zero && fmt.dot == 0) pad = '0';
	while (pad_space > 0) {
		if (write(1, &pad, 1) == -1) { free(num); return -1; }
		count++;
		pad_space--;
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
    int count = 0;
    int write_result;
    int len;
    int pad_zero = 0;
    int prefix = 0;
    int i;
    int pad_space;
    char pad_char;

    hex = ft_xtoa(n, uppercase);
    if (!hex)
        return -1;

    // Calculate lengths and paddings
    len = ft_strlen(hex);
    if (fmt.dot == 1 && fmt.precision == 0 && n == 0)
        len = 0;

    if (fmt.dot == 1 && fmt.precision > len)
        pad_zero = fmt.precision - len;

    if (fmt.hash && n != 0)
        prefix = 2;

    // Calculate total length
    int total = prefix + pad_zero + len;
    if (len == 0)
        total = prefix;

    // Calculate space padding
    pad_space = fmt.width - total;
    if (pad_space < 0)
        pad_space = 0;

    // Determine padding character
    pad_char = ' ';
    if (fmt.zero && !fmt.minus && !fmt.dot)
        pad_char = '0';

    // Right alignment (padding before content)
    if (!fmt.minus)
    {
        // Print prefix first if zero padding
        if (pad_char == '0' && prefix)
        {
            if (uppercase)
                write_result = write(1, "0X", 2);
            else
                write_result = write(1, "0x", 2);

            if (write_result == -1) {
                free(hex);
                return -1;
            }
            count += write_result;
            prefix = 0;
        }

        // Space padding
        i = 0;
        while (i < pad_space)
        {
            write_result = write(1, &pad_char, 1);
            if (write_result == -1) {
                free(hex);
                return -1;
            }
            count += write_result;
            i++;
        }
    }

    // Print prefix if not printed yet
    if (prefix)
    {
        if (uppercase)
            write_result = write(1, "0X", 2);
        else
            write_result = write(1, "0x", 2);

        if (write_result == -1) {
            free(hex);
            return -1;
        }
        count += write_result;
    }

    // Zero padding from precision
    i = 0;
    while (i < pad_zero)
    {
        write_result = write(1, "0", 1);
        if (write_result == -1) {
            free(hex);
            return -1;
        }
        count += write_result;
        i++;
    }

    // Print digits (except when precision=0 and n=0)
    if (!(fmt.dot == 1 && fmt.precision == 0 && n == 0))
    {
        i = 0;
        while (hex[i])
        {
            write_result = write(1, &hex[i], 1);
            if (write_result == -1) {
                free(hex);
                return -1;
            }
            count += write_result;
            i++;
        }
    }

    // Left alignment (padding after content)
    if (fmt.minus)
    {
        i = 0;
        while (i < pad_space)
        {
            write_result = write(1, " ", 1);
            if (write_result == -1) {
                free(hex);
                return -1;
            }
            count += write_result;
            i++;
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
