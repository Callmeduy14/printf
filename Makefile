# Makefile for ft_printf library
# This Makefile compiles the ft_printf library with all required flags

# Library name (must be libftprintf.a as per requirements)
NAME = libftprintf.a

# Compiler and flags (cc with -Wall -Wextra -Werror as required)
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files for the library
SRCS = ft_printf.c handlers.c utils.c

# Object files (generated from source files)
OBJS = $(SRCS:.c=.o)

# Default target: build the library
all: $(NAME)

# Build the library using ar command (required by the subject)
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	rm -f $(OBJS)

# Remove object files and library
fclean: clean
	rm -f $(NAME)

# Rebuild everything from scratch
re: fclean all

# Declare phony targets (targets that don't create files with the same name)
.PHONY: all clean fclean re 