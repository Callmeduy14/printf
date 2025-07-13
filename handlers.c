#include "ft_printf.h"

// Handle character conversion with formatting options
int ft_handle_char(va_list args, t_format *fmt)
{
	char c;
	int count = 0;
	int padding;

	c = va_arg(args, int);
	padding = fmt->width - 1; // Width minus the character itself

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	// Print the character
	count += ft_putchar(c);

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
}

// Handle string conversion with formatting options
int ft_handle_string(va_list args, t_format *fmt)
{
	char *str;
	int count = 0;
	int len;
	int padding;
	int precision_len;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";

	len = ft_strlen(str);
	precision_len = len;

	// Apply precision if specified
	if (fmt->precision_specified && fmt->precision < len)
		precision_len = fmt->precision;

	padding = fmt->width - precision_len;

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	// Print the string (or part of it if precision is specified)
	count += ft_putstr_len(str, precision_len);

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
}

// Handle pointer conversion with formatting options
int ft_handle_pointer(va_list args, t_format *fmt)
{
	unsigned long ptr;
	int count = 0;
	int num_len;
	int padding;
	int precision_padding;

	ptr = (unsigned long)va_arg(args, void *);
	num_len = ft_count_digits_hex(ptr);
	precision_padding = 0;

	// Apply precision padding for hex digits
	if (fmt->precision_specified && fmt->precision > num_len)
		precision_padding = fmt->precision - num_len;

	// Calculate total padding (width - prefix - precision_padding - digits)
	padding = fmt->width - 2 - precision_padding - num_len;

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	// Print prefix "0x"
	count += ft_putstr("0x");

	// Print precision padding (zeros)
	if (precision_padding > 0)
		count += ft_print_padding('0', precision_padding);

	// Print the hex number
	count += ft_putnbr_hex_pointer(ptr);

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
}

// Handle decimal conversion with formatting options
int ft_handle_decimal(va_list args, t_format *fmt)
{
	int n;
	int count = 0;
	int num_len;
	int padding;
	int precision_padding;
	int sign_len = 0;

	n = va_arg(args, int);
	num_len = ft_count_digits(n);

	// Handle special case for INT_MIN
	if (n == -2147483648)
	{
		return (ft_handle_int_min(fmt));
	}

	// Calculate sign length and adjust number
	if (n < 0)
	{
		sign_len = 1;
		n = -n;
	}
	else if (fmt->flag_plus)
		sign_len = 1;
	else if (fmt->flag_space)
		sign_len = 1;

	// Apply precision padding
	precision_padding = 0;
	if (fmt->precision_specified && fmt->precision > num_len)
		precision_padding = fmt->precision - num_len;

	// Calculate total padding
	padding = fmt->width - sign_len - precision_padding - num_len;

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
	{
		if (fmt->flag_zero && !fmt->precision_specified)
			count += ft_print_padding('0', padding);
		else
			count += ft_print_padding(' ', padding);
	}

	// Print sign
	if (n < 0)
		count += ft_putchar('-');
	else if (fmt->flag_plus)
		count += ft_putchar('+');
	else if (fmt->flag_space)
		count += ft_putchar(' ');

	// Print precision padding (zeros)
	if (precision_padding > 0)
		count += ft_print_padding('0', precision_padding);

	// Print the number
	count += ft_putnbr_positive(n);

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
}

// Handle integer conversion (same as decimal)
int ft_handle_integer(va_list args, t_format *fmt)
{
	return (ft_handle_decimal(args, fmt));
}

// Handle unsigned conversion with formatting options
int ft_handle_unsigned(va_list args, t_format *fmt)
{
	unsigned int n;
	int count = 0;
	int num_len;
	int padding;
	int precision_padding;

	n = va_arg(args, unsigned int);
	num_len = ft_count_digits_unsigned(n);

	// Apply precision padding
	precision_padding = 0;
	if (fmt->precision_specified && fmt->precision > num_len)
		precision_padding = fmt->precision - num_len;

	// Calculate total padding
	padding = fmt->width - precision_padding - num_len;

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
	{
		if (fmt->flag_zero && !fmt->precision_specified)
			count += ft_print_padding('0', padding);
		else
			count += ft_print_padding(' ', padding);
	}

	// Print precision padding (zeros)
	if (precision_padding > 0)
		count += ft_print_padding('0', precision_padding);

	// Print the number
	count += ft_putnbr_unsigned(n);

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
}

// Handle hex lowercase conversion with formatting options
int ft_handle_hex_lower(va_list args, t_format *fmt)
{
	unsigned int n;
	int count = 0;
	int num_len;
	int padding;
	int precision_padding;
	int prefix_len = 0;

	n = va_arg(args, unsigned int);
	num_len = ft_count_digits_hex(n);

	// Add prefix length if hash flag is set and number is not zero
	if (fmt->flag_hash && n != 0)
		prefix_len = 2;

	// Apply precision padding
	precision_padding = 0;
	if (fmt->precision_specified && fmt->precision > num_len)
		precision_padding = fmt->precision - num_len;

	// Calculate total padding
	padding = fmt->width - prefix_len - precision_padding - num_len;

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
	{
		if (fmt->flag_zero && !fmt->precision_specified)
			count += ft_print_padding('0', padding);
		else
			count += ft_print_padding(' ', padding);
	}

	// Print prefix if hash flag is set
	if (fmt->flag_hash && n != 0)
		count += ft_putstr("0x");

	// Print precision padding (zeros)
	if (precision_padding > 0)
		count += ft_print_padding('0', precision_padding);

	// Print the hex number
	count += ft_putnbr_hex(n, 0);

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
}

// Handle hex uppercase conversion with formatting options
int ft_handle_hex_upper(va_list args, t_format *fmt)
{
	unsigned int n;
	int count = 0;
	int num_len;
	int padding;
	int precision_padding;
	int prefix_len = 0;

	n = va_arg(args, unsigned int);
	num_len = ft_count_digits_hex(n);

	// Add prefix length if hash flag is set and number is not zero
	if (fmt->flag_hash && n != 0)
		prefix_len = 2;

	// Apply precision padding
	precision_padding = 0;
	if (fmt->precision_specified && fmt->precision > num_len)
		precision_padding = fmt->precision - num_len;

	// Calculate total padding
	padding = fmt->width - prefix_len - precision_padding - num_len;

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
	{
		if (fmt->flag_zero && !fmt->precision_specified)
			count += ft_print_padding('0', padding);
		else
			count += ft_print_padding(' ', padding);
	}

	// Print prefix if hash flag is set
	if (fmt->flag_hash && n != 0)
		count += ft_putstr("0X");

	// Print precision padding (zeros)
	if (precision_padding > 0)
		count += ft_print_padding('0', precision_padding);

	// Print the hex number
	count += ft_putnbr_hex(n, 1);

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
}

// Handle percent conversion with formatting options
int ft_handle_percent(t_format *fmt)
{
	int count = 0;
	int padding;

	padding = fmt->width - 1; // Width minus the percent sign

	// Print left padding if not left-justified
	if (!fmt->flag_minus && padding > 0)
	{
		if (fmt->flag_zero)
			count += ft_print_padding('0', padding);
		else
			count += ft_print_padding(' ', padding);
	}

	// Print the percent sign
	count += ft_putchar('%');

	// Print right padding if left-justified
	if (fmt->flag_minus && padding > 0)
		count += ft_print_padding(' ', padding);

	return (count);
} 