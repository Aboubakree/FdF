/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:32:06 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 02:35:55 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_window	new_window(int x, int y, char *title)
{
	void	*mlx;

	mlx = mlx_init();
	return ((t_window){mlx, mlx_new_window(mlx, x, y, title), x, y});
}

t_img	new_img(int x_window, int y_window, int x_img, int y_img)
{
	t_img	img;

	img.window = new_window(x_window, y_window, "FDF");
	img.img_ptr = mlx_new_image(img.window.window_ptr, x_img, y_img);
	img.img_data = mlx_get_data_addr(img.img_ptr, &img.img_bpp,
			&img.img_size_line, &img.img_endian);
	img.img_width = x_img;
	img.img_height = y_img;
	return (img);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img.img_width && y < img.img_height)
	{
		dst = img.img_data + (y * img.img_size_line) + x * (img.img_bpp / 8);
		*(unsigned int *)dst = color;
	}
}

void	free_map(t_map *map)
{
	t_map	*temp;
	int		i;

	while (map)
	{
		temp = map;
		map = map->next;
		free(temp->line);
		i = 0;
		while (temp->z_plus_color_values[i])
			free(temp->z_plus_color_values[i++]);
		free(temp->z_plus_color_values);
		free(temp);
	}
}

int	exit_tutorial(t_img *img)
{
	if (img)
	{
		if (img->img_ptr)
			mlx_destroy_image(img->window.mlx_ptr, img->img_ptr);
		if (img->window.window_ptr)
			mlx_destroy_window(img->window.mlx_ptr, img->window.window_ptr);
	}
	exit(EXIT_SUCCESS);
}
