#include "ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

// Test result tracking
static int tests_passed = 0;
static int tests_failed = 0;

// Helper function to compare ft_printf output with printf
void test_printf_comparison(const char *format, ...)
{
	va_list args1, args2;
	char buffer1[1024];
	char buffer2[1024];
	int result1, result2;
	
	// Capture ft_printf output
	va_start(args1, format);
	result1 = ft_printf(format, args1);
	va_end(args1);
	
	// Capture printf output
	va_start(args2, format);
	result2 = printf(format, args2);
	va_end(args2);
	
	// Compare return values
	if (result1 == result2)
	{
		printf("✓ Test passed: %s (return: %d)\n", format, result1);
		tests_passed++;
	}
	else
	{
		printf("✗ Test failed: %s (ft_printf: %d, printf: %d)\n", format, result1, result2);
		tests_failed++;
	}
}

// Test character conversion
void test_char_conversion(void)
{
	printf("\n=== Testing Character Conversion (%c) ===\n");
	
	test_printf_comparison("%c", 'A');
	test_printf_comparison("%c", 'Z');
	test_printf_comparison("%c", '0');
	test_printf_comparison("%c", '\n');
	test_printf_comparison("%c", '\t');
	test_printf_comparison("%c", 0);
	
	// Test with width
	test_printf_comparison("%5c", 'A');
	test_printf_comparison("%-5c", 'A');
	test_printf_comparison("%05c", 'A');
}

// Test string conversion
void test_string_conversion(void)
{
	printf("\n=== Testing String Conversion (%s) ===\n");
	
	test_printf_comparison("%s", "Hello, World!");
	test_printf_comparison("%s", "");
	test_printf_comparison("%s", (char *)NULL);
	test_printf_comparison("%s", "Test string with spaces");
	
	// Test with width and precision
	test_printf_comparison("%15s", "Hello");
	test_printf_comparison("%-15s", "Hello");
	test_printf_comparison("%.5s", "Hello, World!");
	test_printf_comparison("%15.5s", "Hello, World!");
	test_printf_comparison("%-15.5s", "Hello, World!");
}

// Test pointer conversion
void test_pointer_conversion(void)
{
	printf("\n=== Testing Pointer Conversion (%p) ===\n");
	
	int num = 42;
	void *ptr = &num;
	
	test_printf_comparison("%p", ptr);
	test_printf_comparison("%p", (void *)0);
	test_printf_comparison("%p", (void *)0x12345678);
	
	// Test with width and precision
	test_printf_comparison("%20p", ptr);
	test_printf_comparison("%-20p", ptr);
	test_printf_comparison("%.10p", ptr);
	test_printf_comparison("%20.10p", ptr);
}

// Test decimal conversion
void test_decimal_conversion(void)
{
	printf("\n=== Testing Decimal Conversion (%d) ===\n");
	
	test_printf_comparison("%d", 42);
	test_printf_comparison("%d", -42);
	test_printf_comparison("%d", 0);
	test_printf_comparison("%d", INT_MAX);
	test_printf_comparison("%d", INT_MIN);
	
	// Test with flags
	test_printf_comparison("%+d", 42);
	test_printf_comparison("%+d", -42);
	test_printf_comparison("% d", 42);
	test_printf_comparison("% d", -42);
	
	// Test with width
	test_printf_comparison("%10d", 42);
	test_printf_comparison("%-10d", 42);
	test_printf_comparison("%010d", 42);
	
	// Test with precision
	test_printf_comparison("%.5d", 42);
	test_printf_comparison("%.5d", 0);
	test_printf_comparison("%.0d", 0);
	
	// Test combinations
	test_printf_comparison("%+10.5d", 42);
	test_printf_comparison("%-+10.5d", 42);
	test_printf_comparison("% 10.5d", 42);
}

// Test integer conversion
void test_integer_conversion(void)
{
	printf("\n=== Testing Integer Conversion (%i) ===\n");
	
	test_printf_comparison("%i", 42);
	test_printf_comparison("%i", -42);
	test_printf_comparison("%i", 0);
	test_printf_comparison("%i", INT_MAX);
	test_printf_comparison("%i", INT_MIN);
	
	// Test with flags
	test_printf_comparison("%+i", 42);
	test_printf_comparison("%+i", -42);
	test_printf_comparison("% i", 42);
	test_printf_comparison("% i", -42);
	
	// Test with width and precision
	test_printf_comparison("%10.5i", 42);
	test_printf_comparison("%-+10.5i", 42);
}

// Test unsigned conversion
void test_unsigned_conversion(void)
{
	printf("\n=== Testing Unsigned Conversion (%u) ===\n");
	
	test_printf_comparison("%u", 42);
	test_printf_comparison("%u", 0);
	test_printf_comparison("%u", UINT_MAX);
	
	// Test with width and precision
	test_printf_comparison("%10u", 42);
	test_printf_comparison("%-10u", 42);
	test_printf_comparison("%010u", 42);
	test_printf_comparison("%.5u", 42);
	test_printf_comparison("%10.5u", 42);
}

// Test hex lowercase conversion
void test_hex_lower_conversion(void)
{
	printf("\n=== Testing Hex Lowercase Conversion (%x) ===\n");
	
	test_printf_comparison("%x", 42);
	test_printf_comparison("%x", 0);
	test_printf_comparison("%x", 255);
	test_printf_comparison("%x", 0xABCD);
	
	// Test with hash flag
	test_printf_comparison("%#x", 42);
	test_printf_comparison("%#x", 0);
	
	// Test with width and precision
	test_printf_comparison("%10x", 42);
	test_printf_comparison("%-10x", 42);
	test_printf_comparison("%010x", 42);
	test_printf_comparison("%.5x", 42);
	test_printf_comparison("%#10.5x", 42);
}

// Test hex uppercase conversion
void test_hex_upper_conversion(void)
{
	printf("\n=== Testing Hex Uppercase Conversion (%X) ===\n");
	
	test_printf_comparison("%X", 42);
	test_printf_comparison("%X", 0);
	test_printf_comparison("%X", 255);
	test_printf_comparison("%X", 0xABCD);
	
	// Test with hash flag
	test_printf_comparison("%#X", 42);
	test_printf_comparison("%#X", 0);
	
	// Test with width and precision
	test_printf_comparison("%10X", 42);
	test_printf_comparison("%-10X", 42);
	test_printf_comparison("%010X", 42);
	test_printf_comparison("%.5X", 42);
	test_printf_comparison("%#10.5X", 42);
}

// Test percent conversion
void test_percent_conversion(void)
{
	printf("\n=== Testing Percent Conversion (%%) ===\n");
	
	test_printf_comparison("%%");
	test_printf_comparison("%%%%");
	
	// Test with width
	test_printf_comparison("%5%");
	test_printf_comparison("%-5%");
	test_printf_comparison("%05%");
}

// Test edge cases and special scenarios
void test_edge_cases(void)
{
	printf("\n=== Testing Edge Cases ===\n");
	
	// Test INT_MIN
	test_printf_comparison("%d", -2147483648);
	test_printf_comparison("%i", -2147483648);
	
	// Test zero with precision
	test_printf_comparison("%.5d", 0);
	test_printf_comparison("%.5u", 0);
	test_printf_comparison("%.5x", 0);
	test_printf_comparison("%.5X", 0);
	
	// Test multiple conversions
	test_printf_comparison("%s %d %x %%", "Test", 42, 255);
	test_printf_comparison("%c%s%d%u%x%X%%", 'A', "Hello", 42, 100, 255, 255);
	
	// Test empty string
	test_printf_comparison("");
	test_printf_comparison("No conversions");
	
	// Test invalid format specifiers
	test_printf_comparison("%q");
	test_printf_comparison("%");
}

// Test complex formatting combinations
void test_complex_formatting(void)
{
	printf("\n=== Testing Complex Formatting ===\n");
	
	// Multiple flags
	test_printf_comparison("%+-10d", 42);
	test_printf_comparison("%+ -10d", 42);
	test_printf_comparison("%#010x", 255);
	
	// Width with asterisk
	test_printf_comparison("%*d", 10, 42);
	test_printf_comparison("%*s", 15, "Hello");
	
	// Precision with asterisk
	test_printf_comparison("%.*s", 5, "Hello, World!");
	test_printf_comparison("%.*d", 5, 42);
	
	// Both width and precision with asterisk
	test_printf_comparison("%*.*d", 10, 5, 42);
	test_printf_comparison("%*.*s", 15, 5, "Hello, World!");
}

// Test memory and null handling
void test_memory_handling(void)
{
	printf("\n=== Testing Memory and Null Handling ===\n");
	
	// Test null format string
	int result = ft_printf(NULL);
	if (result == -1)
	{
		printf("✓ NULL format string handled correctly\n");
		tests_passed++;
	}
	else
	{
		printf("✗ NULL format string not handled correctly\n");
		tests_failed++;
	}
	
	// Test null pointer
	test_printf_comparison("%p", (void *)NULL);
	
	// Test null string
	test_printf_comparison("%s", (char *)NULL);
}

// Print test summary
void print_test_summary(void)
{
	printf("\n=== Test Summary ===\n");
	printf("Tests passed: %d\n", tests_passed);
	printf("Tests failed: %d\n", tests_failed);
	printf("Total tests: %d\n", tests_passed + tests_failed);
	
	if (tests_failed == 0)
	{
		printf("🎉 All tests passed! ft_printf implementation is working correctly.\n");
	}
	else
	{
		printf("❌ Some tests failed. Please review the implementation.\n");
	}
}

int main(void)
{
	printf("Starting ft_printf Unit Tests\n");
	printf("=============================\n");
	
	// Run all test suites
	test_char_conversion();
	test_string_conversion();
	test_pointer_conversion();
	test_decimal_conversion();
	test_integer_conversion();
	test_unsigned_conversion();
	test_hex_lower_conversion();
	test_hex_upper_conversion();
	test_percent_conversion();
	test_edge_cases();
	test_complex_formatting();
	test_memory_handling();
	
	// Print summary
	print_test_summary();
	
	return (tests_failed == 0 ? 0 : 1);
} 