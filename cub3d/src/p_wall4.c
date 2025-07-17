/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:33:40 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 18:37:32 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	is_valid_tile(char c);
int	check_up_tile(char **map, int c, int l);
int	check_down_tile(char **map, int c, int l, int map_height);
char	**check_map_validity(char **map, int map_height, int max_width);

int	is_valid_tile(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'W'
		|| c == 'S');
}

int	check_up_tile(char **map, int c, int l)
{
	int	up_width;

	if (c == 0)
		return (1);
	up_width = ft_strlen(map[c - 1]);
	if (l >= up_width || !is_valid_tile(map[c - 1][l]))
	{
		printf("\n\n\tError: Invalid at line %d column %d (above)\n\n\n",
			c, l);
		return (0);
	}
	return (1);
}

int	check_down_tile(char **map, int c, int l, int map_height)
{
	int	down_width;

	if (c >= map_height - 1)
		return (1);
	down_width = ft_strlen(map[c + 1]);
	if (l >= down_width || !is_valid_tile(map[c + 1][l]))
	{
		printf("\n\n\tError: Invalid at line %d, column %d (below)\n\n\n",
			c, l);
		return (0);
	}
	return (1);
}

char	**check_map_validity(char **map, int map_height, int max_width)
{
	int	l;
	int	c;
	int	current_width;

	l = 0;
	while (l < max_width)
	{
		c = 0;
		while (c < map_height)
		{
			current_width = ft_strlen(map[c]);
			if (l < current_width && map[c][l] == '0')
			{
				if (!check_up_tile(map, c, l) || !check_down_tile(map, c, l,
						map_height))
					return (NULL);
			}
			c++;
		}
		l++;
	}
	return (map);
}