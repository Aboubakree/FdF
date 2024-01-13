/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 02:02:40 by akrid             #+#    #+#             */
/*   Updated: 2024/01/13 06:32:04 by akrid            ###   ########.fr       */
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
	float x_increment;
	float y_increment;
    t_point result_point;
    int     steps;

    steps = get_steps(point1, point2);
	x_increment = (point2.x - point1.x) / (float)steps;
	y_increment = (point2.y - point1.y) / (float)steps;
    result_point.x = point1.x;
    result_point.y = point1.y;
    result_point.color = point1.color;
	mlx_pixel_put(img.window.mlx_ptr, img.window.window_ptr, (int)result_point.x, (int)result_point.y, 0x0000FF);

	for (int k = 0; k < steps; k++)
	{
		result_point.x = result_point.x + x_increment;
		result_point.y = result_point.y + y_increment;
		mlx_pixel_put(img.window.mlx_ptr, img.window.window_ptr, (int)result_point.x, (int)result_point.y, 0x0000FF);
	}
}

void    draw_map(t_img img,t_map  *map, int x_center, int y_center)
{
    t_point point1;
    t_point point2;
    int     i;

    i = 0;
    while (map)
    {
        x_lenth = get_X_lenth(map->z_values) * 10;
        while(j < x_lenth)
        {
            put_pixel_img(img, x_center + j, y_center + i, 0xFFFFFF);
            draw_line(img); 
            j += 10;
        }
        map = map->next;
    }
}

void draw_img_border(t_img img)
{
    int i;
    int j;
    
    i = 0;
    while(i < 880)
    {
        j = 0;
        while(j < 1720)
        {
            if (i == 0 || i == 879 || j == 0 || j == 1719)
                put_pixel_img(img, 0 + j, 0 + i, 0xFFFFFF);
            j ++;
        }
        i ++;
    }
}

void draw_referential_border(t_img img)
{
    int i;

    i = 0;
    while (i < 500)
        put_pixel_img(img, 500, 150 + i++, 0xFFFFFF);
    i = 0;
    while (i < 700)
        put_pixel_img(img, 500 + i++, 150, 0xFFFFFF);
    // center(500,150)
}

int main(int argc, char **argv)
{
    t_img   img;
    t_map   *map;
    t_map   *test;

    map = NULL;
    map = read_map(argc, argv);
    test = map;
    if (!map)
        return (1);
    img = new_img(1920, 1080, 1720, 880);
    draw_img_border(img);
    // draw_referential_border(img);
    draw_map(img, map, 100, 100);
    mlx_put_image_to_window(img.window.mlx_ptr,img.window.window_ptr, img.img_ptr, 100, 100);
    
    mlx_hook(img.window.window_ptr, 17, 0, exit_tutorial, &img);
    mlx_loop(img.window.mlx_ptr);
    return (0);
}
