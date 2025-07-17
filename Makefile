# Nama library
NAME = libftprintf.a

# Kompilator dan flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# File sumber
SRCS = ft_printf.c ft_parse_format.c ft_print_bonus.c ft_conversion_utils.c

# File objek
OBJS = $(SRCS:.c=.o)

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

# Aturan default
all: $(NAME)

# Kompilasi library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Aturan untuk kompilasi file objek
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Membersihkan file objek
clean:
	rm -f $(OBJS)

# Membersihkan file objek dan library
fclean: clean
	rm -f $(NAME)

# Kompilasi ulang
re: fclean all

# Phony targets
.PHONY: all clean fclean re
