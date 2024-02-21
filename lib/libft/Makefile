NAME = libft.a
SRC = ./ft_putnbr_fd.c ./ft_putendl_fd.c ./ft_putstr_fd.c ./ft_putchar_fd.c ./ft_striteri.c ./ft_strjoin.c ./ft_strtrim.c ./ft_strmapi.c ./ft_itoa.c ./ft_memmove.c ./ft_memchr.c ./ft_strlen.c ./ft_isdigit.c ./ft_isalpha.c ./ft_calloc.c ./ft_memcpy.c ./ft_strchr.c ./ft_substr.c ./ft_isalnum.c ./ft_isprint.c ./ft_strdup.c ./ft_strncmp.c ./ft_tolower.c ./ft_toupper.c ./ft_strnstr.c ./ft_strlcat.c ./ft_memset.c ./ft_atoi.c ./ft_bzero.c ./ft_isascii.c ./ft_memcmp.c ./ft_split.c ./ft_strlcpy.c ./ft_strrchr.c  
BONUS = ./ft_lstlast.c ./ft_lstsize.c ./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstadd_back.c ./ft_lstdelone.c ./ft_lstmap.c ./ft_lstiter.c ./ft_lstclear.c
OBJ = $(SRC:%.c=%.o)
OBJ_BONUS = $(BONUS:%.c=%.o)
FLAGS = -Werror -Wextra -Wall

all : $(NAME)
$(NAME) : bonus
	gcc -c $(FLAGS) -I ./ $(SRC)
	ar rcs $(NAME) $(OBJ)
bonus : $(OBJ_BONUS)
	gcc -c $(FLAGS) -I ./ $(BONUS)
	ar rcs $(NAME) $(OBJ_BONUS)
clean :
	rm -f $(OBJ) $(OBJ_BONUS)
fclean : clean
	rm -f $(NAME)
re : fclean all
