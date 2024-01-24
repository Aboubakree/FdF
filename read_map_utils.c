/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:52:06 by akrid             #+#    #+#             */
/*   Updated: 2024/01/24 03:30:03 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*new_line(void)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->line = NULL;
	new->next = NULL;
	return (new);
}

void	add_back(t_map **list, char *line)
{
	t_map	*node;
	t_map	*temp;

	node = new_line();
	if (!node)
		return ;
	node->line = line;
	if (!*list)
		*list = node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

void	get_z_values(t_map **map)
{
	t_map	*temp;

	temp = *map;
	if (temp == NULL)
	{
		ft_printf("No data found !!");
		exit(1);
	}
	while (temp)
	{
		temp->z_plus_color_values = ft_split(temp->line, ' ');
		temp = temp->next;
	}
}

int	ft_lstsize(t_map *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = (lst->next);
	}
	return (i);
}
