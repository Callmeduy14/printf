#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int		my_count;
	int		real_count;
	char	*str = "Hello, World!";
	int		num = 42;
	int		neg_num = -123;
	unsigned int	uns_num = 4294967295;
	int		hex_num = 255;
	void	*ptr = &num;

	printf("=== Testing ft_printf with Bonus Features ===\n\n");

	// Test 1: Basic conversions (mandatory part)
	printf("=== Basic Conversions ===\n");
	
	// Character test
	printf("Character test:\n");
	my_count = ft_printf("ft_printf: %c\n", 'A');
	real_count = printf("printf: %c\n", 'A');
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// String test
	printf("String test:\n");
	my_count = ft_printf("ft_printf: %s\n", str);
	real_count = printf("printf: %s\n", str);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Null string test
	printf("Null string test:\n");
	my_count = ft_printf("ft_printf: %s\n", (char *)NULL);
	real_count = printf("printf: %s\n", (char *)NULL);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Pointer test
	printf("Pointer test:\n");
	my_count = ft_printf("ft_printf: %p\n", ptr);
	real_count = printf("printf: %p\n", ptr);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Decimal test
	printf("Decimal test:\n");
	my_count = ft_printf("ft_printf: %d\n", num);
	real_count = printf("printf: %d\n", num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Negative decimal test
	printf("Negative decimal test:\n");
	my_count = ft_printf("ft_printf: %d\n", neg_num);
	real_count = printf("printf: %d\n", neg_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Integer test
	printf("Integer test:\n");
	my_count = ft_printf("ft_printf: %i\n", num);
	real_count = printf("printf: %i\n", num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Unsigned test
	printf("Unsigned test:\n");
	my_count = ft_printf("ft_printf: %u\n", uns_num);
	real_count = printf("printf: %u\n", uns_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Hex lowercase test
	printf("Hex lowercase test:\n");
	my_count = ft_printf("ft_printf: %x\n", hex_num);
	real_count = printf("printf: %x\n", hex_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Hex uppercase test
	printf("Hex uppercase test:\n");
	my_count = ft_printf("ft_printf: %X\n", hex_num);
	real_count = printf("printf: %X\n", hex_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Percent test
	printf("Percent test:\n");
	my_count = ft_printf("ft_printf: %%\n");
	real_count = printf("printf: %%\n");
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Test 2: Bonus Features - Width and Padding
	printf("=== Bonus Features: Width and Padding ===\n");
	
	// Width test with spaces
	printf("Width test (spaces):\n");
	my_count = ft_printf("ft_printf: [%10d]\n", num);
	real_count = printf("printf: [%10d]\n", num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Width test with zeros
	printf("Width test (zeros):\n");
	my_count = ft_printf("ft_printf: [%010d]\n", num);
	real_count = printf("printf: [%010d]\n", num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Left justification test
	printf("Left justification test:\n");
	my_count = ft_printf("ft_printf: [%-10d]\n", num);
	real_count = printf("printf: [%-10d]\n", num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// String width test
	printf("String width test:\n");
	my_count = ft_printf("ft_printf: [%15s]\n", str);
	real_count = printf("printf: [%15s]\n", str);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Test 3: Bonus Features - Precision
	printf("=== Bonus Features: Precision ===\n");
	
	// Precision test for integers
	printf("Precision test (integers):\n");
	my_count = ft_printf("ft_printf: [%.5d]\n", num);
	real_count = printf("printf: [%.5d]\n", num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Precision test for strings
	printf("Precision test (strings):\n");
	my_count = ft_printf("ft_printf: [%.5s]\n", str);
	real_count = printf("printf: [%.5s]\n", str);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Precision test for hex
	printf("Precision test (hex):\n");
	my_count = ft_printf("ft_printf: [%.8x]\n", hex_num);
	real_count = printf("printf: [%.8x]\n", hex_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Test 4: Bonus Features - Flags
	printf("=== Bonus Features: Flags ===\n");
	
	// Plus flag test
	printf("Plus flag test:\n");
	my_count = ft_printf("ft_printf: [%+d] [%+d]\n", num, neg_num);
	real_count = printf("printf: [%+d] [%+d]\n", num, neg_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Space flag test
	printf("Space flag test:\n");
	my_count = ft_printf("ft_printf: [% d] [% d]\n", num, neg_num);
	real_count = printf("printf: [% d] [% d]\n", num, neg_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Hash flag test for hex
	printf("Hash flag test (hex):\n");
	my_count = ft_printf("ft_printf: [%#x] [%#X]\n", hex_num, hex_num);
	real_count = printf("printf: [%#x] [%#X]\n", hex_num, hex_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Test 5: Complex Combinations
	printf("=== Complex Combinations ===\n");
	
	// Width + precision + flags
	printf("Width + precision + flags:\n");
	my_count = ft_printf("ft_printf: [%+10.5d]\n", num);
	real_count = printf("printf: [%+10.5d]\n", num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Left justify + width + precision
	printf("Left justify + width + precision:\n");
	my_count = ft_printf("ft_printf: [%-10.5s]\n", str);
	real_count = printf("printf: [%-10.5s]\n", str);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Zero padding + hash flag
	printf("Zero padding + hash flag:\n");
	my_count = ft_printf("ft_printf: [%#010x]\n", hex_num);
	real_count = printf("printf: [%#010x]\n", hex_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Test 6: Edge Cases
	printf("=== Edge Cases ===\n");
	
	// INT_MIN test
	printf("INT_MIN test:\n");
	my_count = ft_printf("ft_printf: %d\n", -2147483648);
	real_count = printf("printf: %ld\n", -2147483648L);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Zero with precision
	printf("Zero with precision:\n");
	my_count = ft_printf("ft_printf: [%.5d]\n", 0);
	real_count = printf("printf: [%.5d]\n", 0);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	// Multiple conversions
	printf("Multiple conversions:\n");
	my_count = ft_printf("ft_printf: %s %d %x %%\n", str, num, hex_num);
	real_count = printf("printf: %s %d %x %%\n", str, num, hex_num);
	printf("My count: %d, Real count: %d\n\n", my_count, real_count);

	return (0);
} 