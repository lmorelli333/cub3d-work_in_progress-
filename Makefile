# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 10:39:28 by fcarlucc          #+#    #+#              #
#    Updated: 2024/03/08 18:01:23 by lmorelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = $(wildcard *.c) \
      $(wildcard map/*.c) \
      $(wildcard utils/*.c) \
      $(wildcard raycasting/*.c)

OBJS = $(SRC:.c=.o)

FLAGS := -Wall -Wextra -Werror -g

MLX_FLAGS = -lmlx -lX11 -lXext -lm

MINILIBX_PATH = ./minilibx

MINILIBX = $(MINILIBX_PATH)/libmlx.a

# COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

all: $(NAME)

%.o : %.c
	@cc $(FLAGS) -Imlx -I$(MINILIBX_PATH) -c $< -o $@

$(NAME): $(OBJS) $(MINILIBX)
	@cc $(FLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) -L$(MINILIBX_PATH)

$(MINILIBX):
	@make -C $(MINILIBX_PATH)

clean:
	@rm -f $(OBJS)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re


# NAME = cub3d

# SRC = $(wildcard *.c) \
# 		$(wildcard utils/*.c) \
# 		$(wildcard map/*.c) \

# OBJS = $(SRC:.c=.o)

# FLAGS := -Wall -Wextra -Werror -g

# #COLORS
# RED = \033[1;31m

# GREEN = \033[1;32m

# YELLOW = \033[1;33m

# DEFAULT = \033[0m

# all: $(NAME)

# %.o : %.c
# 	@cc $(FLAGS) -c $< -o $@

# $(NAME): $(OBJS)
# 	@cc $(FLAGS) $(OBJS) -o $(NAME)
# 	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

# clean:
# 	@rm -f $(OBJS)
# 	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

# fclean: clean
# 	@rm -f $(NAME)
# 	@echo "$(RED)all deleted!$(DEFAULT)"

# re: clean fclean all
