/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:30:49 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/23 22:15:20 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "libft/libft.h"

# if defined(__linux__)
#  define PTRNULL "(nil)"
#  define NPTRSIZE 5
# elif defined(__APPLE__)
#  define PTRNULL "0x0"
#  define NPTRSIZE 3
# endif

typedef struct s_format
{
	int		minus;
	int		zero;
	int		width;
	int		precision;
	int		dot;
	int		hash;
	int		space;
	int		plus;
	char	type;
}	t_format;

typedef struct s_intvars
{
	int			is_neg;
	int			len;
	int			print_sign;
	int			pad_zero;
	int			pad_space;
	char		pad_char;
	int			pos;
	t_format	*fmt;
	char		*hex;
}	t_intvars;

int			ft_printf(const char *format, ...);
int			ft_printf_bonus(const char *format, ...);

t_format	ft_parse_format(const char **format, va_list args);
int			ft_handle_format(va_list args, t_format fmt);

void		handle_padding_int(int count, char c, char *buf, int *pos);
void		handle_padding_unsign(char *buffer, int *pos, int pad, char c);
int			calculate_unsigned_padding(t_format fmt, int len,
				unsigned int n, int *paddings);
int			calculate_hex_padding(t_format *fmt, t_intvars *v,
				unsigned int n);
int			calculate_string_padding(t_format fmt, int print_len);
int			write_padding(int count, char c);

void		init_int_vars(int n, t_format fmt, t_intvars *v, char *num);
void		init_hex_vars(t_format *fmt, unsigned int n,
				t_intvars *v, char **hex);
int			write_hex_to_buffer(t_format *fmt, t_intvars *v,
				char *buffer, unsigned int n);
void		handle_sign_int(int n, t_format fmt, char *buf, int *pos);

int			ft_print_char(t_format fmt, int c);
int			ft_print_string(t_format fmt, char *str);
int			ft_print_pointer(t_format fmt, unsigned long ptr);
int			ft_print_int(t_format fmt, int n);
int			ft_print_unsigned(t_format fmt, unsigned int n);
int			ft_print_hex(t_format fmt, unsigned int n);
int			ft_print_percent(t_format fmt);
int			ft_print_pointer_hex(unsigned long n);

char		*ft_utoa(unsigned int n);
char		*ft_xtoa(unsigned long n, int uppercase);

#endif
