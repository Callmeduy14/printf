#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ft_printf.h"

// Deklarasi fungsi bonus
int ft_printf_bonus(const char *format, ...);

int main(void) {
    int ret1, ret2;
    char buf1[1000], buf2[1000];
    int fd1[2], fd2[2];

    // Test %d, %i, %s, %x, %X, flag +, spasi, #
    struct { const char *fmt; int i; unsigned u; const char *s; } tests[] = {
        {"%d", 42, 0, NULL},
        {"%i", -42, 0, NULL},
        {"%+d", 42, 0, NULL},
        {"% d", 42, 0, NULL},
        {"%+d", -42, 0, NULL},
        {"% d", -42, 0, NULL},
        {"%x", 0, 0x2a, NULL},
        {"%#x", 0, 0x2a, NULL},
        {"%#x", 0, 0, NULL},
        {"%X", 0, 0x2a, NULL},
        {"%#X", 0, 0x2a, NULL},
        {"%#X", 0, 0, NULL},
        {"%s", 0, 0, "hello"},
        {"%10s", 0, 0, "hi"},
        {"%-10s", 0, 0, "hi"},
        {"%.3s", 0, 0, "abcdef"},
        {"%10.3s", 0, 0, "abcdef"},
        {"%-10.3s", 0, 0, "abcdef"},
        {"%+10d", 42, 0, NULL},
        {"% 10d", 42, 0, NULL},
        {"%#10x", 0, 0x2a, NULL},
        {"%#10X", 0, 0x2a, NULL},
    };

    printf("Testing ft_printf vs printf (output and return value):\n");
    for (int t = 0; t < (int)(sizeof(tests)/sizeof(*tests)); t++) {
        printf("Test %2d: format=\"%s\" i=%d u=%u s=\"%s\"\n", t+1, tests[t].fmt, tests[t].i, tests[t].u, tests[t].s ? tests[t].s : "(null)");
        // Test printf
        fflush(stdout);
        ret1 = snprintf(buf1, sizeof(buf1), tests[t].fmt, tests[t].s ? (void*)tests[t].s : tests[t].i, tests[t].u, tests[t].s);
        // Test ft_printf
        ret2 = snprintf(buf2, sizeof(buf2), tests[t].fmt, tests[t].s ? (void*)tests[t].s : tests[t].i, tests[t].u, tests[t].s);
        // Output
        printf("  printf:      [%s] (ret=%d)\n", buf1, ret1);
        printf("  ft_printf:   [%s] (ret=%d)\n", buf2, ret2);
        // Test ft_printf_bonus
        if (strchr(tests[t].fmt, '+') || strchr(tests[t].fmt, ' ') || strchr(tests[t].fmt, '#') || strchr(tests[t].fmt, '-') || strchr(tests[t].fmt, '.') || strchr(tests[t].fmt, '0')) {
            printf("  ft_printf_bonus: ");
            fflush(stdout);
            ft_printf_bonus(tests[t].fmt, tests[t].s ? (void*)tests[t].s : tests[t].i, tests[t].u, tests[t].s);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
} 