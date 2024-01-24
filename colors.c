/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 00:03:06 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 03:17:12 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_color_increment(t_point start, t_point end, int steps)
{
	if (start.x == end.x)
		return ((end.y - start.y) / steps);
	if (start.y == end.y)
		return ((end.x - start.x) / steps);
	return ((end.x - start.x) / steps);
}

int	power(int base, int pow)
{
	if (pow == 0)
		return (1);
	return (base * power(base, --pow));
}

int	get_point_color_extended(char *first_hexa, int i)
{
	int	result;
	int	p;

	result = 0;
	p = 0;
	if (i == 0)
		return (0xFFFFFF);
	while (i-- > 0)
	{
		if ((*(first_hexa + i) >= '0' && *(first_hexa + i) <= '9'))
			result += (*(first_hexa + i) - '0') * power(16, p);
		else if ((*(first_hexa + i) >= 'A' && *(first_hexa + i) <= 'F'))
			result += ((*(first_hexa + i) - 'A') + 10) * power(16, p);
		else if ((*(first_hexa + i) >= 'a' && *(first_hexa + i) <= 'f'))
			result += ((*(first_hexa + i) - 'a') + 10) * power(16, p);
		p++;
	}
	return (result);
}

int	get_point_color(char *str)
{
	char	*comma;
	int		i;

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
		else if ((*(comma + 3 + i) >= 'A' && *(comma + 3 + i) <= 'F')
			|| (*(comma + 3 + i) >= 'a' && *(comma + 3 + i) <= 'f'))
			i++;
		else if ((*(comma + 3 + i) >= '0' && *(comma + 3 + i) <= '9'))
			i++;
		else
			return (0xFFFFFF);
	}
	return (get_point_color_extended((comma + 3), i));
}
