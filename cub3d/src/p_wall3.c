/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:54:51 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 18:48:40 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	ft_strlen_skip_empty_line(char *map);
void	free_game_wall(t_game *game);
char	**check_first_char(char **map, int map_height);

int	ft_strlen_skip_empty_line(char *map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	if (map[i] == '\0')
		return (0);
	return (1);
}

void	free_game_wall(t_game *game)
{
	if (game->map)
		free_tab(game->map);
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

char	**check_first_char(char **map, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		if (map[i][0] > 32 && map[i][0] != '1')
		{
			printf("\n\n\tError: Invalid at line %d, column %d\n\n\n", i,
				0);
			return (NULL);
		}
		i++;
	}
	return (map);
}