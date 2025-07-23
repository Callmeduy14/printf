# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 11:35:31 by yyudi             #+#    #+#              #
#    Updated: 2025/07/23 21:26:14 by yyudi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project
NAME		:= libftprintf.a

# Compiler
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar rcs
RM			:= rm -f

# Directories
LIBFT_DIR	:= ./libft

# Source files
SRCS		:= ft_printf.c ft_parse_format.c ft_conversion_utils.c \
				ft_sign.c ft_printf_char.c ft_printf_hex.c \
				ft_printf_pointer.c ft_printf_string.c ft_printf_unsigned.c \
				ft_printf_integer.c ft_padding.c ft_variables.c

BONUS_SRCS	:= ft_printf_bonus.c

# Objects
OBJS		:= $(SRCS:%.c=%.o)
BONUS_OBJS	:= $(BONUS_SRCS:%.c=%.o)

# Libft
LIBFT		:= $(LIBFT_DIR)/libft.a

# Default build (non-bonus)
all: $(NAME)

# Main library build
$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(NAME) compiled successfully!"

# Bonus build
bonus: $(LIBFT) $(OBJS) $(BONUS_OBJS)
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(NAME) with bonus compiled successfully!"

# Libft compilation
$(LIBFT):
	@make -C $(LIBFT_DIR) all

# Compile .c to .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $<"

# Clean object files
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "Object files cleaned!"

# Full clean (objects + library)
fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Full clean completed!"

# Rebuild
re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re
