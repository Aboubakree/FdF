/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:16:30 by akrid             #+#    #+#             */
/*   Updated: 2024/01/12 22:21:54 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"


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

void	get_z_values(t_map	**map)
{
	t_map	*temp;

	temp = *map;
	while (temp)
	{
		temp->z_values = ft_split(temp->line, ' ');
		temp = temp->next;
	}
}

t_map	*read_map(int argc, char **argv)
{
	t_map *map;
	char *line;

	map = NULL;
	if (argc != 2)
		return (0);
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Could not open file %s !!\n", argv[1]);
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
	return (map);
}

int	ft_lstsize(t_map *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i ++;
		lst = (lst -> next);
	}
	return (i);
}