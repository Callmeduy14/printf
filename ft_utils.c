#include "ft_printf.h"

/*
** Mengecek apakah karakter adalah digit (0-9)
** Return: 1 jika digit, 0 jika bukan
*/
int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

/*
** Mencetak n karakter c ke file descriptor fd
** Return: jumlah karakter yang dicetak, -1 jika error
*/
int ft_putnchar_fd(char c, int n, int fd)
{
    int count;
    count = 0;
    // Ulangi n kali
    while (n > 0)
    {
        // Tulis karakter ke fd
        if (write(fd, &c, 1) == -1)
            return (-1);
        count++;
        n--;
    }
    return (count);
}

/*
** Versi sederhana strlen
** Menghitung panjang string s (tidak termasuk null terminator)
** Return: panjang string
*/
int ft_strlen(const char *s)
{
    int len = 0;
    if (!s)
        return 0;
    while (s[len])
        len++;
    return len;
}

/*
** Mencetak karakter ke file descriptor
** Return: jumlah karakter yang dicetak (1 jika sukses, -1 jika error)
*/
int ft_putchar_fd(char c, int fd)
{
    return write(fd, &c, 1);
}

/*
** Mencetak string ke file descriptor
** Return: jumlah karakter yang dicetak, -1 jika error
*/
int ft_putstr_fd(const char *s, int fd)
{
    int count = 0;
    if (!s)
        return 0;
    while (*s)
    {
        if (ft_putchar_fd(*s, fd) < 0)
            return -1;
        count++;
        s++;
    }
    return count;
}