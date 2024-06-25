/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:26:21 by nharraqi          #+#    #+#             */
/*   Updated: 2024/06/18 16:30:10 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line_buffer(int fd, char *line_left, char *buffer);
static char	*set_line(char *line_buffer);

char	*get_next_line(int fd)
{
	static char	*line_left;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(line_left);
		free(buffer);
		line_left = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, line_left, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	line_left = set_line(line);
	return (line);
}

static char	*set_line(char *line_buffer)
{
	char	*line_left;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[i + 1] == 0)
		return (NULL);
	line_left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*line_left == 0)
	{
		free(line_left);
		line_left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
		line_left = NULL;
	}
	line_buffer[i + 1] = 0;
	return (line_left);
}

static char	*fill_line_buffer(int fd, char *line_left, char *buffer)
{
	ssize_t	readed;
	char	*tmp;

	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(line_left);
			return (NULL);
		}
		else if (readed == 0)
			break ;
		buffer[readed] = 0;
		if (!line_left)
			line_left = ft_strdup("");
		tmp = line_left;
		line_left = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line_left);
}

char	*ft_strchr(char *s, int c)
{
	char	i;

	i = c;
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && i == '\0')
		return ((char *)s);
	return (NULL);
}
