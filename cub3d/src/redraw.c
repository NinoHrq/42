/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:05:50 by marvin            #+#    #+#             */
/*   Updated: 2025/07/17 01:21:37 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	move_player(t_game *game);
void	draw_floor_and_ceiling(t_game *game);
void	raycast(t_game *game);
int	redraw(t_game *game);

void	move_player(t_game *game)
{
	t_movement	movement;

	init_movement(&movement);
	handle_forward_backward_movement(game, &movement);
	handle_left_right_movement(game, &movement);
	handle_rotation(game, &movement);
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

void	raycast(t_game *game)
{
	int			x;
	t_raycast	rc;

	x = 0;
	while (x < WIDTH)
	{
		init_raycast(&rc, game, x);
		calculate_step_and_side_dist(&rc, game);
		perform_dda(&rc, game);
		calculate_wall_distance_and_draw_range(&rc, game);
		select_texture_and_calculate_tex_coords(&rc, game);
		draw_wall_column(&rc, game, x);
		draw_sky_and_floor_column(&rc, game, x);
		x++;
	}
}

int	redraw(t_game *game)
{
	move_player(game);
	ft_memset(game->img.addr, 0, WIDTH * HEIGHT
		* (game->img.bits_per_pixel / 8));
	draw_floor_and_ceiling(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}