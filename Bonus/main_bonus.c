#include "ft_printf_bonus.h"
#include <stdio.h>

int main(void)
{
	ft_printf("[%%10d]: [%10d]\n", 42);
	ft_printf("[%%-10d]: [%-10d]\n", 42);
	ft_printf("[%%010d]: [%010d]\n", 42);
	ft_printf("[%%+10d]: [%+10d]\n", 42);
	ft_printf("[%% 10d]: [% 10d]\n", 42);
	ft_printf("[%%#10x]: [%#10x]\n", 42);
	ft_printf("[%%.5d]: [%.5d]\n", 42);
	ft_printf("[%%10.5d]: [%10.5d]\n", 42);
	ft_printf("[%%-10.5d]: [%-10.5d]\n", 42);
	ft_printf("[%%s]: [%s]\n", "hello");
	ft_printf("[%%10s]: [%10s]\n", "hello");
	ft_printf("[%%-10s]: [%-10s]\n", "hello");
	ft_printf("[%%.3s]: [%.3s]\n", "hello");
	ft_printf("[%%p]: [%p]\n", (void*)0x1234abcd);
	ft_printf("[%%u]: [%u]\n", 123456789u);
	ft_printf("[%%x]: [%x]\n", 0xabcdef);
	ft_printf("[%%X]: [%X]\n", 0xabcdef);
	ft_printf("[%%%%]: [%%]\n");
	return 0;
} 