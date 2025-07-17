/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_load_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:29:29 by marvin            #+#    #+#             */
/*   Updated: 2025/07/17 00:39:57 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	load_texture(t_game *game, t_texture *texture, char *path);
void	load_textures(t_game *game);
void	free_game(t_game *game);
void	free_textures_ulimit(t_game *game);
void	free_textures(t_game *game);

void	load_texture(t_game *game, t_texture *texture, char *path)
{
	if (!game->mlx)
	{
		ft_putstr_fd("Error: MLX non initialisé\n", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	texture->img.img = mlx_xpm_file_to_image(game->mlx,
			path, &texture->width, &texture->height);
	if (!texture->img.img)
	{
		ft_putstr_fd("\n\n\tError: Failed to load texture\n\n\n", 2);
		free_textures_ulimit(game);
		free_game(game);
		exit(1);
	}
	texture->img.addr = mlx_get_game_addr(texture->img.img,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
	if (!texture->img.addr)
	{
		free_textures_ulimit(game);
		free_game(game);
		exit(1);
	}
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->no_texture, game->north_texture);
	load_texture(game, &game->so_texture, game->south_texture);
	load_texture(game, &game->we_texture, game->west_texture);
	load_texture(game, &game->ea_texture, game->east_texture);
}

void	free_game(t_game *game)
{
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
	if (game->map)
		free_tab(game->map);
}

void	free_textures_ulimit(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
	{
		free_textures(game);
		if (game->img.img)
		{
			mlx_destroy_image(game->mlx, game->img.img);
			game->img.img = NULL;
		}
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_textures(t_game *game)
{
	if (game->ea_texture.img.img)
	{
		mlx_destroy_image(game->mlx, game->ea_texture.img.img);
		game->ea_texture.img.img = NULL;
	}
	if (game->no_texture.img.img)
	{
		mlx_destroy_image(game->mlx, game->no_texture.img.img);
		game->no_texture.img.img = NULL;
	}
	if (game->we_texture.img.img)
	{
		mlx_destroy_image(game->mlx, game->we_texture.img.img);
		game->we_texture.img.img = NULL;
	}
	if (game->so_texture.img.img)
	{
		mlx_destroy_image(game->mlx, game->so_texture.img.img);
		game->so_texture.img.img = NULL;
	}
}
