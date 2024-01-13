# SRC = fdf.c fdf_utils.c get_next_line.c get_next_line_utils.c read_map.c libft.c ft_split.c

# OBJ = fdf.o fdf_utils.o get_next_line.o get_next_line_utils.o read_map.o libft.o ft_split.o
SRC = test_draw.c
OBJ = test_draw.o

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