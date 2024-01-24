/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:57:53 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 03:26:08 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_r(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	get_g(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

float	get_gradient_color(float start_color, float end_color, float t)
{
	float	red;
	float	green;
	float	blue;

	red = get_r((int)start_color) + t * (get_r((int)end_color)
			- get_r((int)start_color));
	green = get_g((int)start_color) + t * ((int)get_g(end_color)
			- get_g((int)start_color));
	blue = get_b((int)start_color) + t * (get_b((int)end_color)
			- get_b((int)start_color));
	return (create_rgb((int)red, (int)green, (int)blue));
}
