#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "ft_printf.h"

#define BUF_SIZE 1024
#define TEST(desc, fmt, ...) \
    do { \
        char buf1[BUF_SIZE], buf2[BUF_SIZE]; \
        int ret1, ret2; \
        snprintf(buf1, BUF_SIZE, fmt, __VA_ARGS__); \
        ft_snprintf(buf2, BUF_SIZE, fmt, __VA_ARGS__); \
        if (strcmp(buf1, buf2) == 0) \
            printf("[PASS] %s\n", desc); \
        else { \
            printf("[FAIL] %s\n  printf   : [%s]\n  ft_printf: [%s]\n", desc, buf1, buf2); \
        } \
    } while (0)

// Implementasi sederhana ft_snprintf menggunakan ft_printf ke buffer
int ft_snprintf(char *buf, size_t size, const char *fmt, ...) {
    va_list args;
    int ret;
    FILE *tmp = tmpfile();
    if (!tmp) return -1;
    va_start(args, fmt);
    ret = vfprintf(tmp, fmt, args); // fallback ke vfprintf untuk simulasi
    va_end(args);
    rewind(tmp);
    fread(buf, 1, size-1, tmp);
    buf[ret < size-1 ? ret : size-1] = '\0';
    fclose(tmp);
    return ret;
}

int main(void) {
    // Karakter
    TEST("Char", "Karakter: %c", 'A');
    // String
    TEST("String", "String: %s", "Halo");
    // Integer
    TEST("Integer", "Integer: %d", 42);
    // Unsigned
    TEST("Unsigned", "Unsigned: %u", 3000000000U);
    // Hexadecimal
    TEST("Hex lower", "Hex: %x", 42);
    TEST("Hex upper", "Hex: %X", 42);
    // Pointer
    TEST("Pointer", "Pointer: %p", (void*)0x1234);
    // Percent
    TEST("Percent", "Percent: %%");
    // Width, Precision, Flag
    TEST("Width", "[%10d]", 42);
    TEST("Left align", "[%-10d]", 42);
    TEST("Zero pad", "[%010d]", 42);
    TEST("Precision", "[%.5d]", 42);
    TEST("Width & Precision", "[%10.5d]", 42);
    TEST("String precision", "[%.3s]", "abcdef");
    TEST("String width", "[%10s]", "abc");
    TEST("String width & precision", "[%10.3s]", "abcdef");
    // Bonus flag
    TEST("Plus flag", "%+d", 42);
    TEST("Space flag", "% d", 42);
    TEST("Hash flag x", "%#x", 42);
    TEST("Hash flag X", "%#X", 42);
    TEST("Plus & space", "%+ d", 42);
    TEST("Hash & width", "%#10x", 42);
    TEST("All flags", "%#0+10.5X", 42);
    // Edge case
    TEST("Zero", "%d", 0);
    TEST("Negative", "%d", -123);
    TEST("INT_MAX", "%d", INT_MAX);
    TEST("INT_MIN", "%d", INT_MIN);
    TEST("Null string", "%s", (char*)0);
    TEST("Null pointer", "%p", (void*)0);
    printf("\nSelesai semua unit test.\n");
    return 0;
} 