# Nama library
NAME = libftprintf.a

# Kompilator dan flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# File sumber
SRCS = ft_printf.c ft_parse_format.c ft_conversion_utils.c ft_printf_functions.c

BSRC = ft_printf_bonus.c

# File objek
OBJS = $(SRCS:.c=.o)

OBJS_B = $(BSRC:.c=.o)

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

# Aturan default
all: $(NAME)

# Kompilasi library
$(NAME): $(LIBFT) $(OBJS)
	cp	$(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)

$(LIBFT):
		make -C $(LIBFT_PATH) all
# Aturan untuk kompilasi file objek
bonus: $(LIBFT) $(OBJS) $(OBJS_B)
	cp	$(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS) $(OBJS_B)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Membersihkan file objek
clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

# Membersihkan file objek dan library
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

# Kompilasi ulang
re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re
