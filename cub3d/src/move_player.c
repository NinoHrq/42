/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:20:40 by marvin            #+#    #+#             */
/*   Updated: 2025/07/17 01:38:36 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	init_movement(t_movement *movement);
void	handle_forward_backward_movement(t_game *game, t_movement *movement);
void	move_forward_backward(t_game *game, t_movement *movement, int direction);
int	is_near_wall(t_game *game, double new_x, double new_y);
void	draw_floor_and_ceiling(t_game *game);

void	init_movement(t_movement *movement)
{
	movement->move_speed = 0.1;
	movement->rot_speed = 0.05;
	movement->new_x = 0.0;
	movement->new_y = 0.0;
	movement->old_dir_x = 0.0;
	movement->old_plane_x = 0.0;
}

void	handle_forward_backward_movement(t_game *game, t_movement *movement)
{
	if (game->player.key_up)
		move_forward_backward(game, movement, 1);
	if (game->player.key_down)
		move_forward_backward(game, movement, -1);
}

void	move_forward_backward(t_game *game, t_movement *movement, int direction)
{
	double	current_speed;

	current_speed = movement->move_speed;
	movement->new_x = game->player.x
		+ game->player.dir_x * current_speed * direction;
	movement->new_y = game->player.y
		+ game->player.dir_y * current_speed * direction;
	if (!is_near_wall(game, movement->new_x, game->player.y))
	{
		game->player.x = movement->new_x;
	}
	if (!is_near_wall(game, game->player.x, movement->new_y))
	{
		game->player.y = movement->new_y;
	}
}

int	is_near_wall(t_game *game, double new_x, double new_y)
{
	double	dy;
	double	dx;

	dy = -PLAYER_RADIUS;
	while (dy <= PLAYER_RADIUS)
	{
		dx = -PLAYER_RADIUS;
		while (dx <= PLAYER_RADIUS)
		{
			if (game->map[(int)(new_y + dy)][(int)(new_x + dx)] != '0' &&
				game->map[(int)(new_y + dy)][(int)(new_x + dx)] != 'N' &&
				game->map[(int)(new_y + dy)][(int)(new_x + dx)] != 'S' &&
				game->map[(int)(new_y + dy)][(int)(new_x + dx)] != 'W' &&
				game->map[(int)(new_y + dy)][(int)(new_x + dx)] != 'E')
			{
				return (1);
			}
			dx += 0.1;
		}
		dy += 0.1;
	}
	return (0);
}

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(&game->img, x, y, game->c_color);
			else
				put_pixel(&game->img, x, y, game->f_color);
			x++;
		}
		y++;
	}
}
