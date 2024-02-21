# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 19:15:18 by lmorelli          #+#    #+#              #
#    Updated: 2024/02/20 19:16:50 by lmorelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:%.c=%.o)
CC = gcc -c
FLAGS = -Werror -Wall -Wextra

all : $(NAME)
$(NAME) :
	$(CC) $(FLAGS) $(SRC)
	ar rcs $(NAME) $(OBJ)
clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)
re : fclean all