NAME = libftprintf_bonus.a
SRC = \
	ft_printf_bonus.c \
	ft_utils_bonus.c \
	ft_print_char_bonus.c \
	ft_print_str_bonus.c \
	ft_print_nbr_bonus.c \
	ft_print_unsigned_bonus.c \
	ft_print_hex_bonus.c \
	ft_print_ptr_bonus.c \
	ft_print_percent_bonus.c \
	ft_putnbr_bonus.c \
	parse_flags_bonus.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: bonus

bonus: $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all 