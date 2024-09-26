/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:31:58 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/26 06:26:34 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_mesure(t_cor *env, char *file)
{
	int		fd;
	char	*line;
	char	**tab;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("problm de matrice");
	line = get_next_line(fd);
	if (!line)
		error("probleme line = gnl(map_mesure)");
	tab = ft_split(line, ' ');
	while (tab[env->x_max])
	{
		free(tab[env->x_max]);
		env->x_max++;
	}
	while (line)
	{
		free(line);
		env->y_max++;
		line = get_next_line(fd);
	}
	free(line);
	free(tab);
	close(fd);
}

void	check_matrice(t_cor *env, char *file)
{
	int		i;
	int		fd;
	char	*line;
	char	**tab;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
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
		if (i < env->x_max || i > env->x_max)
			error("pas le mm nbr d'elemnt / ligne! (check_matrice)");
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	put_mat_in_tab(t_cor *env, char *file)
{
	int		fd;
	char	*line;
	char	**line_tab;

	fd = open(file, O_RDONLY);
	env->final_tab = malloc(env->y_max * sizeof(int *));
	while (env->y < env->y_max)
	{
		env->final_tab[env->y] = malloc(env->x_max * sizeof(int));
		line = get_next_line(fd);
		line_tab = ft_split(line, ' ');
		free(line);
		env->x = 0;
		while (env->x < env->x_max)
		{
			env->final_tab[env->y][env->x] = ft_atoi(line_tab[env->x]);
			free(line_tab[env->x]);
			env->x++;
		}
		free(line_tab);
		env->y++;
	}
}

void	free_all(t_cor *env)
{
	int	y;

	y = 0;
	while (y < env->y_max)
	{
		free(env->final_tab[y]);
		y++;
	}
	free(env->final_tab);
}

int	error(char *error_message)
{
	ft_printf("%s\n", error_message);
	exit(1);
}
