/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:40:01 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 03:53:59 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

#define ESC 53

typedef struct s_window
{
	void			*mlx_ptr;
	void			*window_ptr;
	int				window_width;
	int				window_height;
}					t_window;

typedef struct s_map
{
	char			*line;
	char			**z_plus_color_values;
	struct s_map	*next;
}					t_map;

typedef struct s_img
{
	t_window		window;
	void			*img_ptr;
	char			*img_data;
	int				img_width;
	int				img_height;
	int				img_bpp; // bits per pixel
	int				img_size_line;
	int				img_endian;
}					t_img;

typedef struct s_point
{
	float			x;
	float			y;
	float			z;
	float			color;
}					t_point;

typedef struct s_referencial
{
	int				window_height;
	int				window_width;
	int				img_height;
	int				img_width;
	int				x_start_origine;
	int				y_start_origine;
	int				scale;
	int				x_axis_lenght;
	int				y_axis_lenght;
	int				projection;
}					t_referencial;

// -------------------- libft -------------------- //
char				*ft_strchr(const char *s, int c);
int					ft_atoi(char *str);
int					get_x_lenth(char **s);
char				**ft_split(char const *s, char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *str);

// -------------------- ft_printf -------------------- //
int					ft_putchar(char c);
int					ft_putstr(const char *s);
int					ft_putnbr(long n);
int					ft_puthex(unsigned long n, char *base, char converge);
int					check_conversion(const char **c, va_list *args);
int					ft_printf(const char *str, ...);

//  -------------------- get_next_line -------------------- //
char				*get_next_line(int fd);

// -------------------- read_map -------------------- //
t_map				*new_line(void);
void				add_back(t_map **list, char *line);
void				get_z_values(t_map **map);
int					ft_lstsize(t_map *lst);
void				free_map(t_map *map);
void				fill_origines(t_referencial *origines, int b);
void				check_map(t_map *map, t_referencial *origines);
t_map				*read_map(int argc, char **argv, t_referencial *origines);

// -------------------- colors -------------------- //
int					get_r(int rgb);
int					get_g(int rgb);
int					get_b(int rgb);
int					create_rgb(int r, int g, int b);
float				get_gradient_color(float start_color, float end_color,
						float t);
float				get_color_increment(t_point start, t_point end, int steps);
int					power(int base, int pow);
int					get_point_color_extended(char *first_hexa, int i);
int					get_point_color(char *str);

// -------------------- draw -------------------- //
int					get_steps(t_point point1, t_point point2);
void				draw_line(t_img img, t_point point1, t_point point2, int k);

// -------------------- fdf -------------------- //
t_window			new_window(int x, int y, char *title);
t_img				new_img(int x_window, int y_window, int x_img, int y_img);
void				put_pixel_img(t_img img, int x, int y, int color);
t_point				get_next_x_point(t_map *map, int j, int y,
						t_referencial origines);
t_point				get_next_y_point(t_map *map, int j, int y,
						t_referencial origines);
t_point				get_current_point(t_map *map, int j, int y,
						t_referencial origines);
void				draw_map_get_x(t_img img, t_map *map,
						t_referencial origines, int y);
void				draw_map_get_y(t_img img, t_map *map,
						t_referencial origines);
int					exit_tutorial(t_img *img);

// -------------------- main -------------------- //
int					main(int argc, char **argv);

#endif