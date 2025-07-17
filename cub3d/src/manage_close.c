/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:58:41 by marvin            #+#    #+#             */
/*   Updated: 2025/07/17 01:00:57 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);
void	manage_close(t_game *game);
int	ft_close(t_game *game);

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC || keycode == QUIT)
		return (ft_close(game));
	if (keycode == W)
		game->player.key_up = TRUE;
	if (keycode == S)
		game->player.key_down = TRUE;
	if (keycode == A)
		game->player.key_left = TRUE;
	if (keycode == D)
		game->player.key_right = TRUE;
	if (keycode == LEFT)
		game->player.left_rotate = TRUE;
	if (keycode == RIGHT)
		game->player.right_rotate = TRUE;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = FALSE;
	if (keycode == S)
		game->player.key_down = FALSE;
	if (keycode == A)
		game->player.key_left = FALSE;
	if (keycode == D)
		game->player.key_right = FALSE;
	if (keycode == LEFT)
		game->player.left_rotate = FALSE;
	if (keycode == RIGHT)
		game->player.right_rotate = FALSE;
	return (0);
}

void	manage_close(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, QUIT, ESC, ft_close, game);
}

int	ft_close(t_game *game)
{
	if (game->img.img)
	{
		mlx_destroy_image(game->mlx, game->img.img);
	}
	free_textures(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_game(game);
	exit(0);
}
