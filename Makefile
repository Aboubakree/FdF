SRC = minilibxTutorial.c

OBJ = minilibxTutorial.o

NAME = fdf

CFLAGS = -Wall -Wextra -Werror -Imlx

all : $(NAME)

$(NAME) : $(OBJ)
	@cc $(CFLAGS) -c $(SRC)
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all