SRC = fdf.c fdf_utils.c get_next_line.c get_next_line_utils.c read_map.c libft.c ft_split.c ft_printf.c printf_utils.c colors.c dda_draw.c gradient_color.c read_map_utils.c main.c

OBJ = fdf.o fdf_utils.o get_next_line.o get_next_line_utils.o read_map.o libft.o ft_split.o ft_printf.o printf_utils.o colors.o dda_draw.o gradient_color.o read_map_utils.o main.o

NAME = fdf

CFLAGS = -Wall -Wextra -Werror -Imlx

all : $(NAME)

$(NAME) : $(OBJ) 
	@cc $(CFLAGS) -c $(SRC) 
	$(CC) $(OBJ) -Imlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean : 
	rm -f $(OBJ)

fclean : clean 
	rm -f $(NAME)

re : fclean all
