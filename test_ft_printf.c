#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "ft_printf.h"

// Deklarasi fungsi bonus jika ada
int ft_printf_bonus(const char *format, ...);

void test_case(const char *desc, const char *fmt, ...)
{
    va_list args1, args2;
    char buf1[1024], buf2[1024];
    int ret1, ret2;
    va_start(args1, fmt);
    va_start(args2, fmt);
    ret1 = vsnprintf(buf1, sizeof(buf1), fmt, args1);
    ret2 = vsnprintf(buf2, sizeof(buf2), fmt, args2);
    va_end(args1);
    va_end(args2);
    printf("%s\n", desc);
    printf("  printf:    [%s] (ret=%d)\n", buf1, ret1);
    printf("  ft_printf: [%s] (ret=%d)\n", buf2, ret2);
    printf("\n");
}

int main(void)
{
    printf("==== BASIC TESTS ====" "\n");
    test_case("Simple string", "Hello, world!\n");
    test_case("Char", "Char: %c\n", 'A');
    test_case("String", "String: %s\n", "Test");
    test_case("Pointer", "Pointer: %p\n", (void*)0x1234);
    test_case("Decimal", "Decimal: %d\n", 42);
    test_case("Integer", "Integer: %i\n", -42);
    test_case("Unsigned", "Unsigned: %u\n", 3000000000U);
    test_case("Hex lower", "Hex: %x\n", 0x2a);
    test_case("Hex upper", "Hex: %X\n", 0x2a);
    test_case("Percent", "Percent: %%\n");

    printf("==== WIDTH & PRECISION ====" "\n");
    test_case("Width", "[%10d]", 42);
    test_case("Left align", "[%-10d]", 42);
    test_case("Zero pad", "[%010d]", 42);
    test_case("Precision", "[%.5d]", 42);
    test_case("Width & Precision", "[%10.5d]", 42);
    test_case("String precision", "[%.3s]", "abcdef");
    test_case("String width", "[%10s]", "abc");
    test_case("String width & precision", "[%10.3s]", "abcdef");

    printf("==== FLAGS BONUS ====" "\n");
    test_case("Plus flag", "%+d", 42);
    test_case("Space flag", "% d", 42);
    test_case("Hash flag x", "%#x", 42);
    test_case("Hash flag X", "%#X", 42);
    test_case("Plus & space", "%+ d", 42);
    test_case("Hash & width", "%#10x", 42);
    test_case("All flags", "%#0+10.5X", 42);

    printf("==== EDGE CASES ====" "\n");
    test_case("Zero", "%d", 0);
    test_case("Negative", "%d", -123);
    test_case("INT_MAX", "%d", INT_MAX);
    test_case("INT_MIN", "%d", INT_MIN);
    test_case("Null string", "%s", (char*)0);
    test_case("Null pointer", "%p", (void*)0);

    return 0;
} 