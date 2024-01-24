/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:16:30 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 03:39:49 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	fill_origines(t_referencial *origines, int b)
{
	origines->window_width = 1920;
	origines->window_height = 1080;
	origines->img_width = (int)((origines->window_width) * 0.8);
	origines->img_height = (int)((origines->window_height) * 0.8);
	origines->x_start_origine = (int)((origines->img_width) * 0.8);
	origines->y_start_origine = (int)((origines->img_height) * 0.5);
	origines->scale = 1;
	origines->projection = 3;
	b = 1;
	while (b && origines->scale < 21)
	{
		b = 0;
		if (origines->x_axis_lenght < ((origines->img_width
					- origines->x_start_origine) / origines->scale))
		{
			origines->scale += 1;
			b = 1;
		}
		if (origines->y_axis_lenght < ((origines->img_height
					- origines->y_start_origine) / origines->scale))
		{
			origines->scale += 1;
			b = 1;
		}
	}
}

void	check_map(t_map *map, t_referencial *origines)
{
	int	b;

	origines->x_axis_lenght = get_x_lenth(map->z_plus_color_values);
	if (map->next)
		map = map->next;
	origines->y_axis_lenght = 1;
	while (map)
	{
		origines->y_axis_lenght++;
		if (origines->x_axis_lenght > get_x_lenth(map->z_plus_color_values))
		{
			ft_printf("Found wrong line length. Exiting.");
			free_map(map);
			exit(1);
		}
		map = map->next;
	}
	b = 1;
	fill_origines(origines, b);
}

int	check_fdf(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		ft_printf("You must insert one file !!");
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 5)
	{
		ft_printf("File must be in format \".fdf\" !!");
		return (0);
	}
	if (ft_strncmp(argv[1] + len - 4, ".fdf", 4) != 0)
	{
		ft_printf("File must be in format \".fdf\" !!");
		return (1);
	}
	return (1);
}

t_map	*read_map(int argc, char **argv, t_referencial *origines)
{
	t_map	*map;
	char	*line;
	int		fd;

	map = NULL;
	if (check_fdf(argc, argv) == 0)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error: Could not open file %s !!\n", argv[1]);
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		add_back(&map, line);
		line = get_next_line(fd);
	}
	close(fd);
	get_z_values(&map);
	check_map(map, origines);
	return (map);
}
