/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:53:14 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 17:18:49 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

char **parse_wall(char **map, t_game *game);
int	found_max_width(char **map);
char	**check_top_border(char **map);
char	**check_bottom_border(char **map, int map_height);
char	**check_bottom_border(char **map, int map_height);

char **parse_wall(char **map, t_game *game)
{
	int	map_height;
	int	max_width;

	map_height = tablen(map);
	max_width = found_max_width(map);
	if (check_top_border(map) == NULL)
		free_game_wall(game);
	if (check_bottom_border(map, map_height) == NULL)
		free_game_wall(game);
	if (check_first_border(map) == NULL)
		free_game_wall(game);
	if (check_inner_lines(map, map_height) == NULL)
		free_game_wall(game);
	if (check_map_validity(map, map_height, max_width) == NULL)
		free_game_wall(game);
	if (check_map(map, map_height, max_width) == NULL)
		free_game_wall(game);
	if (check_first_char(map, map_height) == NULL)
		free_game_wall(game);
	return (map); 
}

int	found_max_width(char **map)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > n)
			n = ft_strlen(map[i]);
		i++;
	}
	return (n);
}

char	**check_top_border(char **map)
{
	int	j;

	j = 0;
	while (map[0][j] != '\0')
	{
		if (map[0][j] != '1' && map[0][j] > 32)
		{
			printf("\n\n\tError: Error\n\n\n");
			return (NULL);
		}
		j++;
	}
	return (map);
}

char	**check_bottom_border(char **map, int map_height)
{
	int	j;

	j = 0;
	while (map[map_height - 1][j] != '\0')
	{
		if (map[map_height - 1][j] != '1' && map[map_height - 1][j] > 32)
		{
			printf("\n\n\tError: Missing border at last line\n\n\n");
			return (NULL);
		}
		j++;
	}
	return (map);
}