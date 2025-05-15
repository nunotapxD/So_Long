# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntomas-a <ntomas-a@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 23:27:55 by ntomas-a          #+#    #+#              #
#    Updated: 2025/05/15 23:27:55 by ntomas-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = checkers.c controls.c ft_utils.c map.c\
		so_long.c imags.c ft_utils2.c\
		
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -Iinc/
MLXFLAGS = -lXext -lX11 -lm -lz
LIBFT = Libft/libft.a
PRINTF = Printf/libftprintf.a
MLX = minilibx-linux/libmlx_Linux.a

NAME = so_long

all: $(NAME) 

.PHONY: all, fclean, re

$(NAME): $(OBJS)
		make -C minilibx-linux/
		make -C Libft/
		make -C Printf/
		cc $(FLAGS) $(OBJS) $(LIBFT) $(MLX) $(PRINTF) $(MLXFLAGS) -o $(NAME) 

clean:
	rm -f $(OBJS)
	make clean -C minilibx-linux/
	make clean -C Libft/
	make clean -C Printf/
	
fclean: clean
	rm -f $(NAME) $(LIBFT) $(PRINTF) $(MLX)

re: fclean all