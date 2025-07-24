/* ************************************************************************** */
/*                                                                            */
/*   File: ft_printf_integer.c                                                 */
/*   Berisi fungsi untuk mencetak integer (signed) dengan format printf        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Menyalin digit angka dari string num ke buffer, skip tanda minus jika negatif
// num: string hasil konversi integer
// is_neg: 1 jika negatif, 0 jika positif
// buf: buffer tujuan
// pos: pointer ke posisi buffer saat ini
static void	copy_digits(char *num, int is_neg, char *buf, int *pos)
{
	char	*d; // Pointer ke digit

	d = num;
	if (is_neg)
		d++; // Lewati tanda minus
	while (*d)
		buf[(*pos)++] = *d++; // Salin digit ke buffer
}

// Menghitung jumlah digit dari integer n (tanpa tanda)
static int	count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1); // 0 tetap 1 digit
	count = 0;
	if (n < 0)
		n = -n; // Abaikan tanda
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

// Estimasi ukuran buffer yang dibutuhkan untuk output integer
// Memperhitungkan width, precision, dan tanda
static int	estimate_output_size(t_format fmt, int n)
{
	int	digits; // Jumlah digit angka
	int	size;   // Estimasi ukuran buffer

	digits = count_digits(n);
	size = digits;
	if (fmt.precision > digits)
		size = fmt.precision; // Precision lebih besar dari digit
	if (n < 0 || fmt.plus || fmt.space)
		size++; // Tambah untuk tanda
	if (fmt.width > size)
		size = fmt.width; // Width lebih besar dari total
	return (size);
}

// Membangun string integer sesuai format ke buffer
// fmt: hasil parsing format
// n: integer yang akan dicetak
// v: variabel bantu
// buffer: buffer tujuan
// return: panjang string hasil
static int	build_int_string(t_format fmt, int n, t_intvars *v, char *buffer)
{
	char	*num; // String hasil konversi integer

	num = ft_itoa(n); // Konversi integer ke string
	if (!num)
		return (-1);
	init_int_vars(n, fmt, v, num); // Inisialisasi variabel bantu
	// Jika padding dengan '0' dan ada tanda, tulis tanda dulu
	if (!fmt.minus && v->pad_char == '0' && v->print_sign)
		handle_sign_int(n, fmt, buffer, &v->pos);
	if (!fmt.minus)
		handle_padding_int(v->pad_space, v->pad_char, buffer, &v->pos); // Padding kiri
	if (v->print_sign && (fmt.minus || v->pad_char != '0'))
		handle_sign_int(n, fmt, buffer, &v->pos); // Tulis tanda jika perlu
	handle_padding_int(v->pad_zero, '0', buffer, &v->pos); // Padding nol
	if (!(fmt.dot && fmt.precision == 0 && n == 0))
		copy_digits(num, v->is_neg, buffer, &v->pos); // Tulis digit utama
	if (fmt.minus)
		handle_padding_int(v->pad_space, ' ', buffer, &v->pos); // Padding kanan
	free(num);
	return (v->pos);
}

// Fungsi utama untuk mencetak integer signed
// fmt: hasil parsing format
// n: integer yang akan dicetak
// return: jumlah karakter yang dicetak
int	ft_print_int(t_format fmt, int n)
{
	char		*buffer;    // Buffer hasil format
	t_intvars	v;         // Variabel bantu
	int			buffer_size;// Ukuran buffer
	int			result;     // Hasil akhir

	buffer_size = estimate_output_size(fmt, n); // Estimasi ukuran buffer
	buffer = (char *)malloc(sizeof(char) * (buffer_size + 1));
	if (!buffer)
		return (-1);
	result = build_int_string(fmt, n, &v, buffer); // Bangun string output
	if (result == -1)
	{
		free(buffer);
		return (-1);
	}
	if (write(1, buffer, result) == -1)
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	return (result);
}
