/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:19:27 by nharraqi          #+#    #+#             */
/*   Updated: 2025/07/17 00:41:10 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void init_game(t_game *game, char *s);
void init_player(t_game *game);
void init_textures(t_game *game);
void init_colors(t_game *game);
void init_layout(t_game *game, char *s);

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
	init_layout(game, s);
	init_player_pos(game);
	init_mlx(game);
	init_colors_int(game);
	load_textures(game);	
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

void init_layout(t_game *game, char *s)
{
	game->start_map = 0;
	game->doc = get_doc(s);
	if(!game->doc)
		exit(1);
	verify_info(game);
	parse_config(game, game->doc);
	if (parse_doc(game->doc, game->start_map))
		exit_properly_parsing(game);
	if (game->floor_color[2] == -1 || game->ceiling_color[2] == -1)
	{
		free_tab(game->doc);
		free_tab(game->map);
		game->map = NULL;
	}
	if (game->map)
		game->map = parse_wall(game->map, game);
		if (game->map)
			player_spawn(game->map, game);
		else
			free_game_texture(game, "");	
}
