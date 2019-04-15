# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/24 14:34:25 by jmocniak          #+#    #+#              #
#    Updated: 2019/04/04 12:59:12 by jmocniak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
LIBFT = libft_printf/libftprintf.a
CC = gcc
INC = includes/ft_ssl.h \
	  libft_printf/includes/ft_printf.h
FLAGS := -Wall -Werror -Wextra -I includes/

SRC = src/ft_ssl.c \
	  src/flags.c \
	  src/string.c \
	  src/dispatch.c \
	  src/md5.c \
	  src/md5_2.c \
	  src/md5_body.c \
	  src/md5_body_2.c \
	  src/md5_body_3.c \
	  src/sha256.c \
	  src/sha256_2.c \
	  src/sha256_3.c \
	  src/stdin.c \
	  src/stdin_2.c \
	  src/output.c \
	  src/error.c

OBJ = src/ft_ssl.o \
	  src/flags.o \
	  src/string.o \
	  src/dispatch.o \
	  src/md5.o \
	  src/md5_2.o \
	  src/md5_body.o \
	  src/md5_body_2.o \
	  src/md5_body_3.o \
	  src/sha256.o \
	  src/sha256_2.o \
	  src/sha256_3.o \
	  src/stdin.o \
	  src/stdin_2.o \
	  src/output.o \
	  src/error.o

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	@echo "making ft_ssl"
	@$(CC) $(FLAGS) $(LIBFT) $(OBJ) -o $(NAME)

$(LIBFT):
	@echo "making libft_printf"
	@make -C libft_printf

clean:
	rm -Rf $(OBJ)
	make -C libft_printf clean

fclean: clean
	rm -f $(NAME)
	make -C libft_printf fclean

re: fclean all

.PHONY: all clean fclean re
