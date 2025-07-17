/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_player2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:19:14 by marvin            #+#    #+#             */
/*   Updated: 2025/07/17 02:10:39 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	check_spawn_validity(char **map, int i, int j, t_game *dt);
void	carry_on(char **map, int i, int j, t_game *dt);
void	last_check_spawn(char **map, int i, int *j, t_game *dt);
void	set_player_position(char **map, int i, int j, t_game *dt);

void	check_spawn_validity(char **map, int i, int j, t_game *dt)
{
	if (j > 0 && (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S'
			|| map[i][j] == 'W'))
		j--;
	last_check_spawn(map, i, &j, dt);
	if (map[i][j + 1] && (map[i][j] == 'N' || map[i][j] == 'E'
			|| map[i][j] == 'S' || map[i][j] == 'W'))
		j++;
	if (map[i][j] != '0' && map[i][j] != '1')
	{
		printf("\n\n\tError: Invalid spawn position at [%d %d]\n\n\n",
			i, j);
		exit_properly_parsing(dt);
	}
	if (j > 0 && (map[i][j] != 'N' && map[i][j] != 'E' && map[i][j] != 'S'
		&& map[i][j] != 'W' && (map[i][j - 1] == 'N' || map[i][j - 1] == 'E'
			|| map[i][j - 1] == 'S' || map[i][j - 1] == 'W')))
		j++;
	if (map[i][j] != 'N' && map[i][j] != 'E' && map[i][j] != 'S'
		&& map[i][j] != 'W' && (map[i][j + 1] == 'N' || map[i][j + 1] == 'E'
			|| map[i][j + 1] == 'S' || map[i][j + 1] == 'W'))
		j++;
	carry_on(map, i, j, dt);
}

void	carry_on(char **map, int i, int j, t_game *dt)
{
	if ((i > 0 && (j >= ft_strlen(map[i - 1]) || map[i - 1][j] == ' ' || map[i
				- 1][j] == '\0')) || (map[i + 1] && (j >= ft_strlen(map[i + 1])
				|| map[i + 1][j] == ' ' || map[i + 1][j] == '\0')) || (j > 0
			&& (map[i][j - 1] == ' ' || map[i][j - 1] == '\0')) || (map[i][j
			+ 1] && (j + 1 >= ft_strlen(map[i]) || map[i][j + 1] == ' '
				|| map[i][j + 1] == '\0')))
	{
		printf("\n\n\tError: Invalid spawn position at [%d %d]\n\n\n",
			i, j);
		exit_properly_parsing(dt);
	}
	if ((i > 0 && (map[i - 1][j] == ' ' || map[i - 1][j] == '\0')) || (map[i
		+ 1] && (map[i + 1][j] == ' ' || map[i + 1][j] == '\0')) || (j > 0
		&& (map[i][j - 1] == ' ' || map[i][j - 1] == '\0')) || ((map[i][j
			+ 1] == ' ' || map[i][j + 1] == '\0')))
	{
		printf("\n\n\tError: Invalid spawn position at [%d %d]\n\n\n",
			i, j);
		exit_properly_parsing(dt);
	}
}

void	last_check_spawn(char **map, int i, int *j, t_game *dt)
{
	if (map[i][*j] != '0' && map[i][*j] != '1')
	{
		printf("\n\n\tError: Invalid spawn position at [%d %d]\n\n\n",
			i, *j);
		exit_properly_parsing(dt);
	}
}

void	set_player_position(char **map, int i, int j, t_game *dt)
{
	dt->player_init_direction = map[i][j];
	dt->index_player[0] = j;
	dt->index_player[1] = i;
}