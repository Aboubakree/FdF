/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 04:38:41 by akrid             #+#    #+#             */
/*   Updated: 2024/01/12 22:20:38 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	ft_atoi(char *str)
{
	int	ng;
	int	res;

	ng = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str ++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			ng = -ng;
		str ++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str ++;
	}
	return (res * ng);
}

int	get_X_lenth(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

