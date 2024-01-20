SRC = fdf.c fdf_utils.c get_next_line.c get_next_line_utils.c read_map.c libft.c ft_split.c ft_printf.c 

OBJ = fdf.o fdf_utils.o get_next_line.o get_next_line_utils.o read_map.o libft.o ft_split.o ft_printf.o 

# SRC = test_colors.c
# OBJ = test_colors.o

NAME = fdf

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -Imlx

all : $(NAME)

$(NAME) : $(OBJ)
	@cc $(CFLAGS) -c $(SRC)
	$(CC) $(OBJ) -g -fsanitize=address -Imlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all