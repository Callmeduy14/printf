#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "ft_printf.h"

int ft_printf_bonus(const char *format, ...);

void test_bonus(const char *desc, const char *fmt, ...)
{
    va_list args1, args2;
    char buf1[1024], buf2[1024];
    int ret1, ret2;
    va_start(args1, fmt);
    va_start(args2, fmt);
    ret1 = vsnprintf(buf1, sizeof(buf1), fmt, args1);
    ret2 = ft_printf_bonus(fmt, args2);
    va_end(args1);
    va_end(args2);
    printf("%s\n", desc);
    printf("  printf:         [%s] (ret=%d)\n", buf1, ret1);
    printf("  ft_printf_bonus: (ret=%d)\n", ret2);
    printf("\n");
}

int main(void)
{
    printf("==== BONUS FLAG TESTS ====" "\n");
    test_bonus("Plus flag", "%+d\n", 42);
    test_bonus("Space flag", "% d\n", 42);
    test_bonus("Hash flag x", "%#x\n", 42);
    test_bonus("Hash flag X", "%#X\n", 42);
    test_bonus("Plus & space", "%+ d\n", 42);
    test_bonus("Hash & width", "%#10x\n", 42);
    test_bonus("All flags", "%#0+10.5X\n", 42);
    test_bonus("Zero pad & minus", "%0-10d\n", 42);
    test_bonus("Width & precision", "%10.5d\n", 42);
    test_bonus("Negative number", "%+d\n", -42);
    test_bonus("Zero", "%#x\n", 0);
    test_bonus("Edge INT_MAX", "%+d\n", INT_MAX);
    test_bonus("Edge INT_MIN", "% d\n", INT_MIN);
    test_bonus("String width & precision", "%10.3s\n", "abcdef");
    test_bonus("Null string", "%10.3s\n", (char*)0);
    return 0;
} 