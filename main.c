/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 00:38:54 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 04:00:09 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	read_keys(int key_pressed, void *param)
{
	t_img	*img;

	img = (t_img *)param;
	if (key_pressed == ESC || !img)
		exit_tutorial(img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_img			img;
	t_map			*map;
	t_referencial	origines;

	map = NULL;
	map = read_map(argc, argv, &origines);
	if (!map)
		return (1);
	img = new_img(origines.window_width, origines.window_height,
			origines.img_width, origines.img_height);
	draw_map_get_y(img, map, origines);
    mlx_key_hook(img.window.window_ptr, read_keys, &img);
	mlx_hook(img.window.window_ptr, 17, 0, exit_tutorial, &img);
	mlx_loop(img.window.mlx_ptr);
	free_map(map);
	return (0);
}
