/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:03:30 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 19:17:16 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	process_spawn_tile(char **map, int i, int j, t_spawn_ctx *ctx);
void	process_tile(char **map, int i, int j, t_spawn_ctx *ctx);
void	check_multiple_spawns(int *d_flag, t_game *dt);
void	player_spawn(char **map, t_game *dt);

void	process_spawn_tile(char **map, int i, int j, t_spawn_ctx *ctx)
{
	check_multiple_spawns(&ctx->d_flag, ctx->dt);
	check_spawn_validity(map, i, j, ctx->dt);
	set_player_position(map, i, j, ctx->dt);
	ctx->d_flag++;
}

void	process_tile(char **map, int i, int j, t_spawn_ctx *ctx)
{
	char	tile;

	tile = map[i][j];
	if (tile == 'N' || tile == 'E' || tile == 'S' || tile == 'W')
		process_spawn_tile(map, i, j, ctx);
	check_invalid_cases(map, i, j, ctx->dt);
}

void	player_spawn(char **map, t_game *dt)
{
	int			i;
	int			j;
	t_spawn_ctx	ctx;

	i = 0;
	ctx.dt = dt;
	ctx.d_flag = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			process_tile(map, i, j, &ctx);
			j++;
		}
		i++;
	}
	if (ctx.d_flag == 0)
	{
		printf("\n\n\tError: No spawn detected\n\n\n");
		exit_properly_parsing(dt);
	}
}
void	check_multiple_spawns(int *d_flag, t_game *dt)
{
	if (*d_flag > 0)
	{
		printf("\n\n\tError: Wrong spawn detected (multiple spawns)\n\n\n");
		exit_properly_parsing(dt);
	}
}

void	check_invalid_cases(char **map, int i, int j, t_game *dt)
{
	if (map[i][j] && (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
			&& map[i][j] != 'E' && map[i][j] != 'S' && map[i][j] != 'W'
			&& map[i][j] > 32))
	{
		printf("\n\n\tError: Invalid case [%d %d]\n\n\n", i, j);
		exit_properly_parsing(dt);
	}
}