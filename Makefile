# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 19:12:48 by lmorelli          #+#    #+#              #
#    Updated: 2024/02/20 19:33:23 by lmorelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKEFLAGS += --silent

# NAME = cub3d
# LIBFT = lib/libft/libft.a
# PRINTF = lib/ft_printf/libftprintf.a
# #GNL = lib/get_next_line/get_next_line.a
# MLX				=	./libmlx.dylib
# MLX_FLAGS		=	-Lmlx -lmlx -framework OpenGL -framework AppKit

# src = \
# 		src/cub3d.c

# OBJ = $(src:%.c=%.o)

# FLAGS = -Wall -Werror -Wextra -g

# CC = gcc 

# all: $(NAME)

# $(NAME) : $(OBJ)
# 	make all bonus -C lib/libft
# 	make -C lib/ft_printf
# #	make -C lib/get_next_line
# 	make -C lib/mlx
# 	$(CC) $(OBJ) $(FLAGS) $(LIBFT) $(PRINTF) $(MLX_FLAGS) -o cub3d
# 	@echo "\033[32mCub3d compiled\033[0m"
# clean:
# 	make clean -C lib/libft
# 	make clean -C lib/ft_printf
# #	make clean -C lib/get_next_line
# 	make clean -C lib/mlx
# 	rm -f $(OBJ)
# 	@echo "\033[33mObjects removed\033[0m"

# fclean: clean
# 	make fclean -C lib/libft
# 	make fclean -C lib/ft_printf
# #	make fclean -C lib/get_next_line
# 	make fclean -C lib/mlx
# 	rm -f $(NAME)
# 	@echo "\033[33m& the name too\033[0m"

# re: fclean all

# .PHONY:		all clean fclean re



MINILIBX_PATH	=	lib/mlx
MINILIBX		=	$(MINILIBX_PATH)/libmlx.a
LIBFT_PATH		=	lib/libft
LIBFT			=	$(LIBFT_PATH)/libft.a
PRINTF_PATH		=   lib/ft_printf
PRINTF			=   $(PRINTF_PATH)/libftprintf.a
GNL_PATH		=   lib/get_next_line
GNL				=   $(GNL_PATH)/get_next_line.a

SRC	=	src/cub3d.c

HEADER			=	./cub3d.h

OBJECTS			= 	$(SRC:%.c=%.o)

NAME			=	cub3d

CC				=	gcc

RM				=	rm -f

MLX				=	./libmlx.dylib

CFLAGS			=	-Wall -Wextra -Werror

MLX_FLAGS		=	-lmlx -framework OpenGL -framework AppKit

all:			$(NAME)

$(NAME):	$(OBJECTS) $(LIBFT) $(PRINTF) $(GNL)
				$(CC) ${CFLAGS} -c $(SRC) -Imlx
				$(CC) $(OBJECTS) $(LIBFT) $(PRINTF) $(GNL) $(MLX_FLAGS) -o $(NAME)

$(MINILIBX):
				make -C $(MINILIBX_PATH)

$(LIBFT):
				make -C $(LIBFT_PATH)

$(PRINTF):
				make -C $(PRINTF_PATH)

$(GNL):
				make -C $(GNL_PATH)

				@echo "\033[32mCub3d compiled\033[0m"

clean:
				${RM} ${OBJECTS}
				make clean -C ${LIBFT_PATH}
				make clean -C ${PRINTF_PATH}
				make clean -C ${GNL_PATH}
				make clean -C ${MINILIBX_PATH}
				@echo "\033[33mObjects removed\033[0m"

fclean:			clean
					rm -f $(NAME)
					rm -f $(MINILIBX)
					rm -f $(LIBFT)
					rm -f $(PRINTF)
					rm -f $(GNL)
					@echo "\033[33m& the name too\033[0m"

re:				fclean all

.PHONY:			all clean re