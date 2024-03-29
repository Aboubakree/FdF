/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:50:29 by akrid             #+#    #+#             */
/*   Updated: 2024/01/09 02:55:46 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_completed_line(char *buff, char **pre_line)
{
	char	*new_line;

	new_line = ft_strjoin(*pre_line, buff);
	if (*pre_line != NULL)
		free(*pre_line);
	return (new_line);
}

char	*final_line(char **line)
{
	char	*temp;
	char	*line_returned;
	char	*address;

	temp = ft_strdup(*line);
	if (*line != NULL)
		free(*line);
	address = ft_strchr(temp, '\n');
	if (address == NULL)
	{
		*line = ft_substr(NULL, 0, 0);
		line_returned = ft_strdup(temp);
	}
	else
	{
		*line = ft_substr(temp, (address - temp) + 1, ft_strlen(temp));
		if (ft_strlen(*line) == 0)
		{
			free(*line);
			*line = NULL;
		}
		line_returned = ft_substr(temp, 0, (address - temp));
	}
	free(temp);
	return (line_returned);
}

void	*reading_failed(char **line)
{
	if (*line != NULL)
		free(*line);
	*line = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*line = NULL;
	char		*last;
	ssize_t		s;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, buff, 0))
		return (reading_failed(&line));
	s = BUFFER_SIZE;
	while (ft_strchr(line, '\n') == NULL && s == BUFFER_SIZE)
	{
		s = read(fd, buff, BUFFER_SIZE);
		if (s < 1)
		{
			if (line != NULL && line[0] != '\0' && s != -1)
			{
				last = line;
				line = NULL;
				return (last);
			}
			return (reading_failed(&line));
		}
		buff[s] = '\0';
		line = get_completed_line(buff, &line);
	}
	return (final_line(&line));
}
