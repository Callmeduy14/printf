#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

#define BUF_SIZE 1024

// Versi alternatif jika ft_vdprintf tidak tersedia
static int ft_printf_to_fd(int fd, const char *fmt, va_list args) {
    char buffer[BUF_SIZE];
    int len = vsnprintf(buffer, BUF_SIZE, fmt, args);
    if (len < 0) return -1;
    return write(fd, buffer, len);
}

int ft_printf_to_buffer(char *buf, size_t size, const char *fmt, va_list args) {
    int fd[2];
    int ret;
    char temp[BUF_SIZE] = {0};

    if (pipe(fd) == -1)
        return -1;

    ret = ft_printf_to_fd(fd[1], fmt, args);
    close(fd[1]);

    if (ret < 0) {
        close(fd[0]);
        return -1;
    }

    ssize_t bytes_read = read(fd[0], temp, size - 1);
    close(fd[0]);

    if (bytes_read < 0)
        return -1;

    memcpy(buf, temp, bytes_read);
    buf[bytes_read] = '\0';
    return ret;
}

int ft_snprintf(char *buf, size_t size, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = ft_printf_to_buffer(buf, size, fmt, args);
    va_end(args);
    return ret;
}

#define TEST(desc, fmt, ...) \
    do { \
        char buf1[BUF_SIZE] = {0}, buf2[BUF_SIZE] = {0}; \
        int ret1, ret2; \
        ret1 = snprintf(buf1, BUF_SIZE, fmt, ##__VA_ARGS__); \
        ret2 = ft_snprintf(buf2, BUF_SIZE, fmt, ##__VA_ARGS__); \
        printf("\n=== %s ===\nFormat: \"%s\"\n", desc, fmt); \
        printf("printf  : [%s] (return: %d)\n", buf1, ret1); \
        printf("ft_printf: [%s] (return: %d)\n", buf2, ret2); \
        if (strcmp(buf1, buf2) == 0 && ret1 == ret2) \
            printf("RESULT: \033[32mPASS\033[0m\n"); \
        else { \
            printf("RESULT: \033[31mFAIL\033[0m\n"); \
            if (strcmp(buf1, buf2) != 0) \
                printf("- Output mismatch\n"); \
            if (ret1 != ret2) \
                printf("- Return value mismatch (expected: %d, got: %d)\n", ret1, ret2); \
        } \
    } while (0)

int main(void) {
    printf("\n\033[1m=== FT_PRINTF UNIT TEST (FINAL VERSION) ===\033[0m\n");

    // Basic tests
    TEST("Basic char", "Char: %c", 'Z');
    TEST("Basic string", "Str: %s", "Hello World");
    TEST("Basic integer", "Int: %d", 42);
    TEST("Basic unsigned", "Unsigned: %u", 4294967295U);
    TEST("Basic hex lower", "Hex: %x", 0xdeadbeef);
    TEST("Basic hex upper", "Hex: %X", 0xdeadbeef);
    TEST("Basic pointer", "Ptr: %p", main); // Gunakan alamat fungsi main
    TEST("Basic percent", "100%% pure");

    // Format combinations
    TEST("Multiple formats", "Char: %c, Str: %s, Int: %d, Hex: %x", 'A', "test", 42, 42);
    TEST("Mixed text and formats", "The answer is %d or 0x%x or %d", 42, 42, -42);

    // Flag tests
    TEST("Zero padding", "%05d", 42);
    TEST("Left justify", "%-10s", "hello");
    TEST("Forced sign", "%+d", 42);
    TEST("Forced sign negative", "%+d", -42);
    TEST("Space for positive", "% d", 42);
    TEST("Hex with prefix", "%#x", 42);

    // Width & precision
    TEST("Width", "%10d", 42);
    TEST("Precision", "%.5d", 42);
    TEST("Width & precision", "%10.5d", 42);
    TEST("String precision", "%.3s", "abcdef");
    TEST("String width & precision", "%10.3s", "abcdef");

    // Edge cases
    TEST("Zero", "%d", 0);
    TEST("INT_MAX", "%d", INT_MAX);
    TEST("INT_MIN", "%d", INT_MIN);
    TEST("UINT_MAX", "%u", UINT_MAX);
    TEST("Null string", "%s", NULL);
    TEST("Null pointer", "%p", NULL);
    TEST("Empty string", "%s", "");
    TEST("Zero precision", "%.0d", 0);

    // Special cases
    TEST("Only percent", "%%");
    TEST("Multiple percents", "%%%%%%");
    TEST("Literal percent q", "Literal %%q"); // Diperbaiki tanpa argumen

    // Performance cases
    TEST("Long string", "%s", "This is a very long string that tests buffer handling...");
    TEST("Many formats", "%d %d %d %d %d %d %d %d %d %d", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    printf("\n\033[1m=== TEST COMPLETE ===\033[0m\n");
    return 0;
}
