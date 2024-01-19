/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:40:01 by akrid             #+#    #+#             */
/*   Updated: 2024/01/16 18:25:25 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <mlx.h>

typedef struct s_window
{
    void        *mlx_ptr;
    void        *window_ptr;
    int         window_width;
    int         window_height;
}            t_window;

typedef struct s_img
{
    t_window    window;
    void        *img_ptr;
    char        *img_data;
    int         img_width;
    int         img_height;
    int         img_bpp; // bits per pixel
    int         img_size_line;
    int         img_endian;
}            t_img;

typedef struct s_map
{
    char            *line;
    char            **z_plus_color_values;
    struct s_map    *next;
}           t_map;

typedef struct s_point
{
    float     x;
    float     y;
    float     z;
    int     color;
}              t_point;

typedef struct s_referencial
{
    int window_height;
    int window_width;
    int img_height;
    int img_width;
    int x_start_origine;
    int y_start_origine;
    int scale;
    int	x_axis_lenght;
    int	y_axis_lenght;
}               t_referencial;

char	    *ft_strchr(const char *s, int c);
char	    **ft_split(char const *s, char c);
t_window    new_window(int x, int y, char  *title);
t_img       new_img(int x_window, int y_window, int x_img, int y_img);
void        put_pixel_img(t_img img, int x, int y, int color);
t_map       *new_line();
void        add_back(t_map **list, char *line);
t_map       *read_map(int argc, char **argv, t_referencial *origines);
int         exit_tutorial(t_img *img);
int	        get_X_lenth(char **s);
int	        ft_atoi(char *str);
int	        ft_lstsize(t_map *lst);
int         ft_printf(const char *str, ...);

#endif