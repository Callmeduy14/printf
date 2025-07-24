/* ************************************************************************** */
/*                                                                            */
/*   File: ft_printf_string.c                                                  */
/*   Berisi fungsi untuk mencetak string dengan padding, precision, dan flag   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Fungsi untuk menangani string NULL, mengembalikan string pengganti
// str: string input (bisa NULL)
// nullstr: string pengganti jika str NULL
// return: pointer ke string yang akan dicetak
static char	*handle_null_string(char *str, const char *nullstr)
{
	if (!str)
		return ((char *)nullstr); // Jika NULL, pakai "(null)"
	return (str); // Jika tidak NULL, pakai string asli
}

// Menulis sebagian string sebanyak len karakter ke stdout
// str: string yang akan ditulis
// len: jumlah karakter yang akan ditulis
// return: jumlah karakter yang berhasil ditulis, atau -1 jika error
static int	write_string_part(const char *str, int len)
{
	int		written; // Jumlah karakter yang sudah ditulis
	int		ret;     // Hasil write per iterasi

	written = 0;
	while (written < len)
	{
		ret = write(1, str + written, len - written); // Tulis sisa string
		if (ret == -1)
			return (-1); // Jika gagal, return error
		written += ret; // Tambah ke total
	}
	return (written); // Kembalikan jumlah karakter yang ditulis
}

// Menulis string dengan padding (spasi) di kiri/kanan sesuai flag
// fmt: hasil parsing format
// str: string yang akan dicetak
// print_len: panjang string yang akan dicetak (bisa dipotong oleh precision)
// return: jumlah karakter yang dicetak
static int	write_padded_string(t_format fmt, char *str, int print_len)
{
	int	total_len; // Total karakter yang dicetak
	int	pad_space; // Jumlah padding spasi
	int	written;   // Hasil write per bagian

	total_len = 0;
	pad_space = calculate_string_padding(fmt, print_len); // Hitung padding
	if (!fmt.minus && pad_space > 0)
	{
		written = write_padding(pad_space, ' '); // Padding kiri
		if (written == -1)
			return (-1);
		total_len += written;
	}
	written = write_string_part(str, print_len); // Tulis string utama
	if (written == -1)
		return (-1);
	total_len += written;
	if (fmt.minus && pad_space > 0)
	{
		written = write_padding(pad_space, ' '); // Padding kanan
		if (written == -1)
			return (-1);
		total_len += written;
	}
	return (total_len);
}

// Fungsi utama untuk mencetak string dengan format
// fmt: hasil parsing format
// str: string yang akan dicetak
// return: jumlah karakter yang dicetak
int	ft_print_string(t_format fmt, char *str)
{
	const char	*nullstr;       // String pengganti jika str NULL
	char		*processed_str;   // String yang akan dicetak
	int			print_len;       // Panjang string yang akan dicetak

	nullstr = "(null)"; // Standar pengganti string NULL
	processed_str = handle_null_string(str, nullstr); // Handle NULL
	print_len = ft_strlen(processed_str); // Hitung panjang string
	// Jika ada precision, batasi panjang string
	if (fmt.dot == 1 && fmt.precision >= 0 && fmt.precision < print_len)
		print_len = fmt.precision;
	return (write_padded_string(fmt, processed_str, print_len));
}
