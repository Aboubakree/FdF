/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 00:12:53 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 03:44:01 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_steps(t_point point1, t_point point2)
{
	int	dx;
	int	dy;
	int	steps;

	dx = 0;
	dy = 0;
	steps = 0;
	if (point1.x > point2.x)
		dx = point1.x - point2.x;
	else if (point1.x <= point2.x)
		dx = point2.x - point1.x;
	if (point1.y > point2.y)
		dy = point1.y - point2.y;
	else if (point1.y <= point2.y)
		dy = point2.y - point1.y;
	if (dx > dy)
		steps = dx;
	else if (dx <= dy)
		steps = dy;
	return (steps);
}

void	draw_line(t_img img, t_point point1, t_point point2, int k)
{
	float	x_increment;
	float	y_increment;
	t_point	result_point;

	x_increment = (point2.x - point1.x) / (float)get_steps(point1, point2);
	y_increment = (point2.y - point1.y) / (float)get_steps(point1, point2);
	result_point.x = point1.x;
	result_point.y = point1.y;
	result_point.color = point1.color;
	put_pixel_img(img, (int)result_point.x, (int)result_point.y,
		(int)result_point.color);
	k = 0;
	while (k < get_steps(point1, point2))
	{
		result_point.x += x_increment;
		result_point.y += y_increment;
		result_point.color = get_gradient_color(point2.color, point1.color,
				get_color_increment(result_point, point2, get_steps(point1,
						point2)));
		put_pixel_img(img, (int)result_point.x, (int)result_point.y,
			(int)result_point.color);
		k++;
	}
}
