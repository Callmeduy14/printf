/* ************************************************************************** */
/*                                                                            */
/*   File: ft_printf_pointer.c                                                 */
/*   Berisi fungsi untuk mencetak pointer (alamat memori) dengan format printf */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Cetak nilai pointer dalam format hex (tanpa prefix)
static int	print_pointer_hex(unsigned long n, int *total)
{
	char	*str;
	int		ret;

	str = ft_xtoa(n, 0); // Konversi ke string hex
	if (!str)
		return (0);
	ret = write(1, str, ft_strlen(str)); // Cetak string hex
	free(str);
	if (ret == -1)
		return (0);
	*total += ret;
	return (1);
}

// Hitung panjang output pointer (termasuk prefix)
static int	get_pointer_len(unsigned long ptr)
{
	char	*str;
	int		len;

	if (ptr == 0)
		return (3); // "0x0"
	str = ft_xtoa(ptr, 0);
	if (!str)
		return (-1);
	len = ft_strlen(str) + 2; // Tambah 2 untuk "0x"
	free(str);
	return (len);
}

// Cetak isi pointer: prefix "0x" lalu hex, atau "0" jika NULL
static int	print_pointer_content(unsigned long ptr, int *total)
{
	if (write(1, "0x", 2) == -1)
		return (0);
	*total += 2;
	if (ptr == 0)
	{
		if (write(1, "0", 1) == -1)
			return (0);
		(*total)++;
	}
	else if (!print_pointer_hex(ptr, total))
		return (0);
	return (1);
}

// Cetak padding spasi untuk pointer
static int	print_pointer_padding(int width, int len, int *total)
{
	int	padding;

	padding = width - len;
	while (padding-- > 0)
	{
		if (write(1, " ", 1) == -1)
			return (0);
		(*total)++;
	}
	return (1);
}

// Fungsi utama untuk mencetak pointer dengan format
int	ft_print_pointer(t_format fmt, unsigned long ptr)
{
	int	total;
	int	len;

	total = 0;
	len = get_pointer_len(ptr); // Hitung panjang output
	if (len == -1)
		return (-1);
	if (!fmt.minus && fmt.width > len)
		if (!print_pointer_padding(fmt.width, len, &total))
			return (-1);
	if (!print_pointer_content(ptr, &total))
		return (-1);
	if (fmt.minus && fmt.width > len)
		if (!print_pointer_padding(fmt.width, len, &total))
			return (-1);
	return (total);
}
