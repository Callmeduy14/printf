#include "ft_printf.h"

// Print a single character and return 1 (number of characters printed)
int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

// Print a string and return the number of characters printed
int ft_putstr(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

// Print a string with a specific length and return the number of characters printed
int ft_putstr_len(char *str, int len)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && i < len)
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

// Print padding characters (spaces or zeros) and return the number printed
int ft_print_padding(char c, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

// Print a positive integer (helper function for decimal/integer conversion)
int ft_putnbr_positive(int n)
{
	int count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_positive(n / 10);
	count += ft_putchar(n % 10 + '0');
	return (count);
}

// Print an integer with sign handling (original function for backward compatibility)
int ft_putnbr(int n)
{
	int count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr("-2147483648");
		return (count);
	}
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10);
	count += ft_putchar(n % 10 + '0');
	return (count);
}

// Print an unsigned integer and return the number of characters printed
int ft_putnbr_unsigned(unsigned int n)
{
	int count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_unsigned(n / 10);
	count += ft_putchar(n % 10 + '0');
	return (count);
}

// Print a number in hexadecimal format (lowercase or uppercase)
int ft_putnbr_hex(unsigned long n, int uppercase)
{
	int count;
	char *hex_chars;

	count = 0;
	if (uppercase)
		hex_chars = "0123456789ABCDEF";
	else
		hex_chars = "0123456789abcdef";
	if (n >= 16)
		count += ft_putnbr_hex(n / 16, uppercase);
	count += ft_putchar(hex_chars[n % 16]);
	return (count);
}

// Print a pointer address in hexadecimal format (always lowercase)
int ft_putnbr_hex_pointer(unsigned long n)
{
	int count;
	char *hex_chars;

	count = 0;
	hex_chars = "0123456789abcdef";
	if (n >= 16)
		count += ft_putnbr_hex_pointer(n / 16);
	count += ft_putchar(hex_chars[n % 16]);
	return (count);
}

// Count the number of digits in an integer
int ft_count_digits(int n)
{
	int count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

// Count the number of digits in an unsigned integer
int ft_count_digits_unsigned(unsigned int n)
{
	int count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

// Count the number of hexadecimal digits in a number
int ft_count_digits_hex(unsigned long n)
{
	int count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		count++;
		n /= 16;
	}
	return (count);
}

// Handle the special case of INT_MIN (-2147483648) with formatting
int ft_handle_int_min(t_format *fmt)
{
	int count = 0;
	int padding;
	int sign_len = 1; // Always has a minus sign

	// Calculate padding (width - sign - 10 digits)
	padding = fmt->width - sign_len - 10;

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	// Print the sign
	count += ft_putchar('-');

	// Print the number (2147483648)
	count += ft_putstr("2147483648");

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
}

// Get the length of a string
int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// Print a character to a specific file descriptor
void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
} 