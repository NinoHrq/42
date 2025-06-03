/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:19:27 by nharraqi          #+#    #+#             */
/*   Updated: 2025/06/03 19:42:05 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_game(t_game *game, char *s)
{
	game->no_texture.img.img = NULL;
	game->so_texture.img.img = NULL;
	game->we_texture.img.img = NULL;
	game->ea_texture.img.img = NULL;
	game->img.img = NULL;
	game->mlx = NULL;
	game->win = NULL;
    init_player(game);
	init_textures(game);
	init_colors(game);
	
}

void init_player(t_game *game)
{
	game->player.key_up = NULL;
	game->player.key_down = NULL;
	game->player.key_left = NULL;
	game->player.key_right = NULL;
	game->player.left_rotate = NULL;
	game->player.right_rotate = NULL;
}

void init_textures(t_game *game)
{
	game->north_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->south_texture = NULL;
}

void init_colors(t_game *game)
{
	game->floor_color[1] = -1;
	game->ceiling_color[1] = -1;
}
