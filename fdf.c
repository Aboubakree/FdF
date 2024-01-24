/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 02:02:40 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 03:23:29 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_next_x_point(t_map *map, int j, int y, t_referencial origines)
{
	t_point	point;

	point.x = (j + 1) * origines.scale + origines.x_start_origine;
	point.y = y * origines.scale + origines.y_start_origine;
	point.z = ft_atoi(map->z_plus_color_values[j + 1]);
	point.color = get_point_color(map->z_plus_color_values[j + 1]);
	if (origines.projection == 3)
	{
		point.x = 0.7071 * (point.x - point.y);
		point.y = 0.4082 * (point.x + point.y) - point.z;
	}
	return (point);
}

t_point	get_next_y_point(t_map *map, int j, int y, t_referencial origines)
{
	t_point	point;

	point.x = j * origines.scale + origines.x_start_origine;
	point.y = (y + 1) * origines.scale + origines.y_start_origine;
	point.z = ft_atoi(map->z_plus_color_values[j]);
	point.color = get_point_color(map->z_plus_color_values[j]);
	if (origines.projection == 3)
	{
		point.x = 0.7071 * (point.x - point.y);
		point.y = 0.4082 * (point.x + point.y) - point.z;
	}
	return (point);
}

t_point	get_current_point(t_map *map, int j, int y, t_referencial origines)
{
	t_point	current_point;

	current_point.x = j * origines.scale + origines.x_start_origine;
	current_point.y = y * origines.scale + origines.y_start_origine;
	current_point.z = ft_atoi(map->z_plus_color_values[j]);
	current_point.color = get_point_color(map->z_plus_color_values[j]);
	if (origines.projection == 3)
	{
		current_point.x = 0.7071 * (current_point.x - current_point.y);
		current_point.y = 0.4082 * (current_point.x + current_point.y)
			- current_point.z;
	}
	return (current_point);
}

void	draw_map_get_x(t_img img, t_map *map, t_referencial origines, int y)
{
	t_point	current_point;
	t_point	next_point;
	int		j;
	int		k_helper;

	j = 0;
	k_helper = 0;
	while (j < origines.x_axis_lenght)
	{
		current_point = get_current_point(map, j, y, origines);
		if (j < origines.x_axis_lenght - 1)
		{
			next_point = get_next_x_point(map, j, y, origines);
			draw_line(img, current_point, next_point, k_helper);
		}
		if (y < origines.y_axis_lenght - 1)
		{
			next_point = get_next_y_point(map->next, j, y, origines);
			draw_line(img, current_point, next_point, k_helper);
		}
		j++;
	}
}

void	draw_map_get_y(t_img img, t_map *map, t_referencial origines)
{
	int	i;

	i = 0;
	while (i < origines.y_axis_lenght && map)
	{
		draw_map_get_x(img, map, origines, i);
		i++;
		map = map->next;
	}
	if (origines.x_axis_lenght > 1 || origines.y_axis_lenght > 1)
		mlx_put_image_to_window(img.window.mlx_ptr, img.window.window_ptr,
			img.img_ptr, origines.window_width * 0.15, origines.window_height
			* 0.15);
}
