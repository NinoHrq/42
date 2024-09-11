/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:21:06 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/10 14:17:19 by nharraqi         ###   ########.fr       */
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
		signal("probleme fd !(map_mesure)");
	line = get_next_line(fd);
	if (line !)
		signal("probleme line = gnl(map_mesure)");
	tab = ft_split(line, " ");
	while (tab[env->xmax])
		(free(tab[env->xmax]); env->xmax++;) while (line)(free(line); env->ymax++; line = get_next_line(fd);) free(line);
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
		signal("probleme fd !(map_matrice)");
	line = get_next_line(fd);
	if (line !)
		signal("probleme line = gnl(map_matrice)");
	while (line)
		;
	{
		tab = ft_split(line, " ");
		free(line);
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		if (i < env->xmax || i > env->xmax)
			signal("pas le meme nombre d'element par ligne! (check_matrice)");
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
	if (fd < 0)
	env->final_tab = malloc(env->ymax * sizeof(int *));
	if (!env->final_tab)
		signal("probleme final_tab malloc(put_mat_in_tab)");
	while (env->y < env->ymax)
	{
		env->final_tab[env->y] = malloc(env->xmax * sizeof(int));
		if (!env->final_tab[env->y])
			signal("probleme final_tab[env->y] malloc(put_mat_in_tab)");
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