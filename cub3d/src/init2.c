/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:53:06 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 21:21:07 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	init_player_pos(t_game *game);
void	init_mlx(t_game *game);
void	init_colors_int(t_game *game);
int	rgb_tab_to_int(int tab[3]);

void	init_player_pos(t_game *game)
{
	if (game->map)
	{
		game->player.x = game->index_player[0] + 0.5;
		game->player.y = game->index_player[1] + 0.5;
		if (game->player_init_direction == 'N')
			game->player.angle = 3 * PI / 2;
		else if (game->player_init_direction == 'S')
			game->player.angle = PI / 2;
		else if (game->player_init_direction == 'E')
			game->player.angle = 0;
		else if (game->player_init_direction == 'W')
			game->player.angle = PI;
		game->player.dir_x = cos(game->player.angle);
		game->player.dir_y = sin(game->player.angle);
		game->player.plane_x = -game->player.dir_y * 0.66;
		game->player.plane_y = game->player.dir_x * 0.66;
	}
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Erreur : Impossible d'initialiser la bibliothèque MLX.\n");
		return ;
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
	{
		printf("Impossible de créer la fenêtre (dimensions : %d x %d).\n",
			WIDTH, HEIGHT);
		return ;
	}
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
	{
		printf("Impossible de créer l'image (dimensions : %d x %d).\n", WIDTH,
			HEIGHT);
		return ;
	}
	game->img.addr = mlx_get_game_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
}

void	init_colors_int(t_game *game)
{
	game->f_color = rgb_tab_to_int(game->floor_color);
	game->c_color = rgb_tab_to_int(game->ceiling_color);
	if (game->f_color == -1 || game->c_color == -1)
	{
		printf("\n\n\tError: Invalid floor or ceiling color\n\n\n");
		exit(EXIT_FAILURE);
	}
}

int	rgb_tab_to_int(int tab[3])
{
	return ((tab[0] << 16) | (tab[1] << 8) | tab[2]);
}
