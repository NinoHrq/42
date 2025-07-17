/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:50:48 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 18:57:37 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	is_above_cell_valid(char **map, int c, int l);
int	is_below_cell_valid(char **map, int c, int l, int map_height);
int	is_cell_valid(char **map, int c, int l, int map_height);
char	**check_map(char **map, int map_height, int max_width);

int	is_above_cell_valid(char **map, int c, int l)
{
	int	up_width;

	up_width = ft_strlen(map[c - 1]);
	if (l >= up_width || (map[c - 1][l] != '0' && map[c - 1][l] != '1' && map[c
			- 1][l] != 'N' && map[c - 1][l] != 'E' && map[c - 1][l] != 'W'
			&& map[c - 1][l] != 'S'))
	{
		printf("\n\n\tError: Invalid 0 at line %d, column %d\n\n\n", c,
			l);
		return (0);
	}
	return (1);
}

int	is_below_cell_valid(char **map, int c, int l, int map_height)
{
	int	down_width;

	(void)map_height;
	down_width = ft_strlen(map[c + 1]);
	if (l >= down_width || (map[c + 1][l] != '0' && map[c + 1][l] != '1'
			&& map[c + 1][l] != 'N' && map[c + 1][l] != 'E' && map[c
			+ 1][l] != 'W' && map[c + 1][l] != 'S'))
	{
		printf("\n\n\tError: Invalid 0 at line %d, column %d\n\n\t", c, l);
		return (0);
	}
	return (1);
}

int	is_cell_valid(char **map, int c, int l, int map_height)
{
	if (map[c][l] == '0')
	{
		if (c > 0 && !is_above_cell_valid(map, c, l))
		{
			return (0);
		}
		if (c < map_height - 1 && !is_below_cell_valid(map, c, l, map_height))
		{
			return (0);
		}
	}
	return (1);
}

char	**check_map(char **map, int map_height, int max_width)
{
	int	l;
	int	current_width;
	int	c;

	l = 0;
	while (l < max_width)
	{
		c = 0;
		while (c < map_height)
		{
			current_width = ft_strlen(map[c]);
			if (l >= current_width)
			{
				c++;
				continue ;
			}
			if (!is_cell_valid(map, c, l, map_height))
				return (NULL);
			c++;
		}
		l++;
	}
	return (map);
}