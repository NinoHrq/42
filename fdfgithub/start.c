/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:21:06 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/13 22:41:15 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_mesure(coord *env, char *file)
{
	int		fd;
	char	*line;
	char	**tab;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_putendl_fd("probleme fd (map_mesure)", 1);
	line = get_next_line(fd);
	if (!line)
		ft_putendl_fd("probleme line = gnl(map_mesure)", 1);
	tab = ft_split(line, ' ');
	while (tab[env->xmax])
	{
		free(tab[env->xmax]);
		env->xmax++;
	}
	while (line)
	{
		free(line);
		env->ymax++;
		line = get_next_line(fd);
	}
	free(line);
	free(tab);
	close(fd);
}

void	check_matrice(coord *env, char *file)
{
	int		i;
	int		fd;
	char	*line;
	char	**tab;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_putendl_fd("probleme fd (check_matrice)", 1);
	line = get_next_line(fd);
	if (!line)
		ft_putendl_fd("probleme line = gnl(check_matrice)", 1);
	while (line)
	{
		tab = ft_split(line, ' ');
		free(line);
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		if (i < env->xmax || i > env->xmax)
			ft_putendl_fd("pas le meme nombre d'element par ligne! (check_matrice)",
				1);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	put_mat_in_tab(coord *env, char *file)
{
	int fd;
	char *line;
	char **line_tab;

	fd = open(file, O_RDONLY);
	env->final_tab = malloc(env->ymax * sizeof(int *));
	if (!env->final_tab)
		ft_putendl_fd("probleme final_tab malloc(put_mat_in_tab)", 1);
	while (env->y < env->ymax)
	{
		env->final_tab[env->y] = malloc(env->xmax * sizeof(int));
		if (!env->final_tab[env->y])
			ft_putendl_fd("probleme final_tab[env->y] malloc(put_mat_in_tab)",1);
		line = get_next_line(fd);
		line_tab = ft_split(line, ' ');
		free(line);
		env->x = -1;
		while (++env->x < env->xmax)
		{
			env->final_tab[env->y][env->x] = ft_atoi(line_tab[env->x]);
			free(line_tab[env->x]);
		}
		env->y++;
		free(line_tab);
	}
}