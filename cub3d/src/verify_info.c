/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:54:55 by nharraqi          #+#    #+#             */
/*   Updated: 2025/06/10 17:31:28 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void verify_info(t_game *game);
void free_game_texture(t_game *game, char *txt);
void	free_tab(char **tab);

void verify_info(t_game *game)
{
	int i;
	int count_identifier;
	char *line;

	i = 0;
	count_identifier = 0;
	if (!game || !game->doc)
		return ;
	while (game->doc[i])
	{
		line = skip_spaces(game->doc[1]);
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ",
				3) == 0 || ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line,
				"C ", 2) == 0)
			count_identifier++;
		i++;
	}
	if (count_identifier != 6)
		free_game_texture(game, "\n Wrong number of identifier \n");
}

void free_game_texture(t_game *game, char *txt)
{
	printf("%s", txt);
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->east_texture)
		free(game->east_texture);
	if (game->west_texture)
		free(game->west_texture);	
	if (game->doc)
		free_tab(game->doc);
	exit(1);	
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}
