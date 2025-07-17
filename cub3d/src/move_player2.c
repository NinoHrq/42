/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:30:03 by marvin            #+#    #+#             */
/*   Updated: 2025/07/17 01:39:33 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	handle_left_right_movement(t_game *game, t_movement *movement);
void	move_left_right(t_game *game, t_movement *movement, int direction);
void	handle_rotation(t_game *game, t_movement *movement);
void	rotate_player(t_game *game, t_movement *movement, int direction);
void	put_pixel(t_img *img, int x, int y, int color);

void	handle_left_right_movement(t_game *game, t_movement *movement)
{
	if (game->player.key_left)
		move_left_right(game, movement, -1);
	if (game->player.key_right)
		move_left_right(game, movement, 1);
}

void	move_left_right(t_game *game, t_movement *movement, int direction)
{
	double	current_speed;

	current_speed = movement->move_speed;
	movement->new_x = game->player.x
		+ game->player.plane_x * current_speed * direction;
	movement->new_y = game->player.y
		+ game->player.plane_y * current_speed * direction;
	if (!is_near_wall(game, movement->new_x, game->player.y))
	{
		game->player.x = movement->new_x;
	}
	if (!is_near_wall(game, game->player.x, movement->new_y))
	{
		game->player.y = movement->new_y;
	}
}

void	handle_rotation(t_game *game, t_movement *movement)
{
	if (game->player.left_rotate)
		rotate_player(game, movement, -1);
	if (game->player.right_rotate)
		rotate_player(game, movement, 1);
}

void	rotate_player(t_game *game, t_movement *movement, int direction)
{
	movement->old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x
		* cos(direction * movement->rot_speed)
		- game->player.dir_y * sin(direction * movement->rot_speed);
	game->player.dir_y = movement->old_dir_x
		* sin(direction * movement->rot_speed)
		+ game->player.dir_y * cos(direction * movement->rot_speed);
	movement->old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(direction * movement->rot_speed)
		- game->player.plane_y * sin(direction * movement->rot_speed);
	game->player.plane_y = movement->old_plane_x
		* sin(direction * movement->rot_speed)
		+ game->player.plane_y * cos(direction * movement->rot_speed);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
