#include "ft_printf.h"

int main() {
    ft_printf("Hello %s! Number: %d, Hex: %x, Char: %c, Pointer: %p, Unsigned: %u, Percent: %%\n",
        "World", 42, 255, 'A', &main, 3000000000U);
    return 0;
} 