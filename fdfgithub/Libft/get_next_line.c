/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:26:21 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/26 01:32:49 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > 1023)
	{
		free(save);
		free(buffer);
		save = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = fill_line_buffer(fd, save, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	save = set_line(line);
	return (line);
}

char	*set_line(char *line_buffer)
{
	char	*save;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[i + 1] == 0)
		return (NULL);
	save = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*save == 0)
	{
		free(save);
		save = NULL;
	}
	line_buffer[i + 1] = 0;
	return (save);
}

char	*fill_line_buffer(int fd, char *save, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(save);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!save)
			save = ft_strdup("");
		tmp = save;
		save = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (save);
}

/*#include <stdio.h>

int	main(void)
{
	int			fd;
	char		*line;
	const char	*filename = "demain_VH.txt";

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	if (close(fd) == -1)
	{
		ft_printf("Error closing file");
		return (1);
	}
	return (0);
}
*/