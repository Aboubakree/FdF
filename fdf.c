/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 02:02:40 by akrid             #+#    #+#             */
/*   Updated: 2024/01/19 18:14:42 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int get_steps(t_point point1, t_point point2)
{
	int dx;
	int dy;
    int steps;

    dx = point1.x > point2.x ? point1.x - point2.x : point2.x - point1.x;
	dy = point1.y > point2.y ? point1.y - point2.y : point2.y - point1.y;
    steps = dx > dy ? dx : dy;
    return (steps);
    
}

void draw_line(t_img img, t_point point1, t_point point2)
{
	float   x_increment;
	float   y_increment;
    t_point result_point;
    int     k;

	x_increment = (point2.x - point1.x) / (float)get_steps(point1, point2);
	y_increment = (point2.y - point1.y) / (float)get_steps(point1, point2);
    result_point.x = point1.x;
    result_point.y = point1.y;
    result_point.color = point1.color;
	put_pixel_img(img, (int)result_point.x, (int)result_point.y, 0xFFFFFF);
    k = 0;
	while(k < get_steps(point1, point2))
	{
		result_point.x = result_point.x + x_increment;
		result_point.y = result_point.y + y_increment;
		put_pixel_img(img, (int)result_point.x, (int)result_point.y, 0xFFFFFF);
        k++;
	}
}

int power(int base,int pow)
{
    if (pow == 0)
        return (1);
    return (base * power(base, -- pow));
}

int get_point_color_extended(char *first_hexa, int i)
{
    int result;
    int p;

    result = 0;
    p = 0;
    if (i == 0)
        return (0xFFFFFF);
    while(i-- > 0)
    {
        if ((*(first_hexa + i) >= '0' && *(first_hexa + i) <= '9'))
            result += (*(first_hexa + i) - '0') * power(16, p);
        else if ((*(first_hexa + i) >= 'A' && *(first_hexa + i) <= 'F'))
            result += ((*(first_hexa + i) - 'A') + 10) * power(16, p);
        else if ((*(first_hexa + i) >= 'a' && *(first_hexa + i) <= 'f'))
            result += ((*(first_hexa + i) - 'a') + 10) * power(16, p);
        p ++;
    }
    return (result);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;

	i = 0;
	while (s && s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i ++;
	}
	if ((unsigned char)c == (unsigned char) '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int get_point_color(char *str)
{
    char    *comma;
    int     i;
    
    comma = ft_strchr(str, ',');
    if (comma == NULL)
        return (0xFFFFFF);
    if ((*(comma + 1) == '\0') || (*(comma + 1) != '0'))
        return (0xFFFFFF);
    if ((*(comma + 2) == '\0') || (*(comma + 2) != 'x'))
        return (0xFFFFFF);
    i = 0;
    while (*(comma + 3 + i))
    {
        if (i > 6)
            return (0xFFFFFF);
        else if ((*(comma + 3 + i) >= 'A' && *(comma + 3 + i) <= 'F') || (*(comma + 3 + i) >= 'a' && *(comma + 3 + i) <= 'f'))
            i ++;
        else if ((*(comma + 3 + i) >= '0' && *(comma + 3 + i) <= '9'))
            i ++;
        else
            return (0xFFFFFF);
    }
    return (get_point_color_extended((comma + 3), i));
}

t_point get_next_X_point(t_map *map, int j, int y, t_referencial origines)
{
    t_point point;

    point.x = (j + 1) * origines.scale + origines.x_start_origine;
    point.y = y * origines.scale + origines.y_start_origine;
    point.z = ft_atoi(map->z_plus_color_values[j + 1]);
    point.color = get_point_color(map->z_plus_color_values[j + 1]);
    return (point);
}

t_point get_next_Y_point(t_map *map, int j, int y, t_referencial origines)
{
    t_point point;

    point.x = j * origines.scale + origines.x_start_origine;
    point.y = (y + 1) * origines.scale + origines.y_start_origine;
    point.z = ft_atoi(map->z_plus_color_values[j]);
    point.color = get_point_color(map->z_plus_color_values[j]);
    return (point);
}

void   draw_map_get_X(t_img img,t_map  *map, t_referencial origines, int y)
{
    t_point current_point;
    t_point next_point;
    int     j;
    
    j = 0;
    while (j < origines.x_axis_lenght)
    {
        current_point.x = j * origines.scale + origines.x_start_origine;
        current_point.y = y * origines.scale + origines.y_start_origine;
        current_point.z = ft_atoi(map->z_plus_color_values[j]);  
        current_point.color = get_point_color(map->z_plus_color_values[j]);
        if (j < origines.x_axis_lenght - 1)
        {
            next_point = get_next_X_point(map, j, y, origines);
            draw_line(img, current_point, next_point);
        }
        if (y < origines.y_axis_lenght - 1)
        {
            next_point = get_next_Y_point(map->next, j, y, origines);
            draw_line(img, current_point, next_point);
        }
        j ++;
    }
}

void    draw_map_get_Y(t_img img,t_map  *map, t_referencial origines)
{
    int     i;

    i = 0;
    while (i < origines.y_axis_lenght && map)
    {
        draw_map_get_X( img, map, origines, i);
        i ++;
        map = map->next;
    }
    if (origines.x_axis_lenght > 1 || origines.y_axis_lenght > 1)
        mlx_put_image_to_window(img.window.mlx_ptr,img.window.window_ptr, img.img_ptr,
                                origines.window_width * 0.15, origines.window_height * 0.15);
}

void draw_img_border(t_img img)
{
    int i;
    int j;
    
    i = 0;
    while(i < img.img_height)
    {
        j = 0;
        while(j < img.img_width)
        {
            if (i == 0 || i == img.img_height - 1 || j == 0 || j == img.img_width - 1)
                put_pixel_img(img, 0 + j, 0 + i, 0xFFFFFF);
            j ++;
        }
        i ++;
    }
}

int main(int argc, char **argv)
{
    t_img           img;
    t_map           *map;
    t_referencial   origines;

    map = NULL;
    map = read_map(argc, argv, &origines);
    if (!map)
        return (1);
    img = new_img(origines.window_width, origines.window_height, origines.img_width, origines.img_height);
    draw_img_border(img);
    draw_map_get_Y(img, map, origines);
    
    mlx_hook(img.window.window_ptr, 17, 0, exit_tutorial, &img);
    mlx_loop(img.window.mlx_ptr);
    return (0);
}
