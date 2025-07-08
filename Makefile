# **************************************************************************** #
#                               MAKEFILE                                      #
# **************************************************************************** #

NAME = printf
SRC = ft_printf.c main.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME_BONUS = printf_bonus
SRC_BONUS = ft_printf_bonus.c ft_parse_bonus.c ft_print_d_bonus.c ft_print_s_bonus.c ft_print_x_bonus.c ft_print_u_bonus.c ft_print_c_bonus.c ft_print_p_bonus.c ft_print_percent_bonus.c main_bonus.c
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

bonus: $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus 