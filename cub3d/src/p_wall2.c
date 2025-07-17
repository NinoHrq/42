/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:19:27 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 17:54:38 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

char	**check_first_border(char **map);
void	check_null_line(char *line, int i);
int	check_right_border(char *line, int map_width, int i);
int	check_zero_surroundings(char **map, int i, int j, int map_height);
char	**check_inner_lines(char **map, int map_height);

char	**check_first_border(char **map)
{
	int	iii;
	int	jjj;

	iii = 0;
	jjj = 0;
	while (map[iii])
	{
		jjj = 0;
		while (map[iii][jjj])
		{
			if (jjj > 0 && ((map[iii][jjj] == '0' && map[iii][jjj - 1] <= 32)
					|| (map[iii][jjj] == '0' && map[iii][jjj + 1] <= 32)))
			{
				printf("\n\n\tError: Problem at line %d, column %d\n\n\n",
					iii, jjj);
				return (NULL);
			}
			jjj++;
		}
		iii++;
	}
	return (map);
}

void	check_null_line(char *line, int i)
{
	(void)i;
	if (line == NULL)
	{
		printf("Error : NULL line detected\n");
		exit(1);
	}
}

int	check_right_border(char *line, int map_width, int i)
{
	if (map_width > 0 && line[map_width - 1] != '1')
	{
		printf("\n\n\tError: Missing border at line %d\n\n\n", i);
		return (0);
	}
	return (1);
}

int	check_zero_surroundings(char **map, int i, int j, int map_height)
{
	if ((i > 0 && j < ft_strlen(map[i - 1]) && map[i - 1][j] == ' ')
		|| (i < map_height - 1 && j < ft_strlen(map[i + 1]) && map[i
			+ 1][j] == ' ') || (j > 0 && map[i][j - 1] == ' ')
		|| (j < ft_strlen_skip_empty_line(map[i]) - 1 && map[i][j + 1] == ' '))
	{
		printf("\n\n\tError: Invalid 0 at line %d, column %d\n\n\n", i,
			j);
		return (0);
	}
	return (1);
}

char	**check_inner_lines(char **map, int map_height)
{
	int	i;
	int	j;
	int	map_width;

	i = 1;
	while (i < map_height - 1)
	{
		check_null_line(map[i], i);
		map_width = ft_strlen_skip_empty_line(map[i]);
		if (!check_right_border(map[i], map_width, i))
			return (NULL);
		j = 0;
		while (j < map_width)
		{
			if (map[i][j] == '0')
			{
				if (!check_zero_surroundings(map, i, j, map_height))
					return (NULL);
			}
			j++;
		}
		i++;
	}
	return (map);
}