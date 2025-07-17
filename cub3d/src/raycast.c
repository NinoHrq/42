/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:40:18 by marvin            #+#    #+#             */
/*   Updated: 2025/07/17 01:45:33 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	raycast(t_game *game);
void	init_raycast(t_raycast *rc, t_game *game, int x);
void	calculate_x_step_and_side_dist(t_raycast *rc, t_game *game);
void	calculate_y_step_and_side_dist(t_raycast *rc, t_game *game);
void	calculate_step_and_side_dist(t_raycast *rc, t_game *game);

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

void	init_raycast(t_raycast *rc, t_game *game, int x)
{
	rc->camera_x = 2 * x / (double)WIDTH - 1;
	rc->ray_dir_x = game->player.dir_x + game->player.plane_x * rc->camera_x;
	rc->ray_dir_y = game->player.dir_y + game->player.plane_y * rc->camera_x;
	rc->map_x = (int)(game->player.x);
	rc->map_y = (int)(game->player.y);
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
	rc->side_dist_x = 0.0;
	rc->side_dist_y = 0.0;
	rc->step_x = 0;
	rc->step_y = 0;
	rc->hit = 0;
	rc->side = 0;
	rc->perp_wall_dist = 0.0;
	rc->line_height = 0;
	rc->draw_start = 0;
	rc->draw_end = 0;
	rc->out_screen = 0;
	rc->wall_x = 0.0;
	rc->tex_x = 0;
	rc->tex_y = 0;
	rc->texture = NULL;
}

void	calculate_x_step_and_side_dist(t_raycast *rc, t_game *game)
{
	if (fabs(rc->ray_dir_x) < EPSILON)
	{
		rc->step_x = 0;
		rc->side_dist_x = 0;
	}
	else if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player.x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player.x) * rc->delta_dist_x;
	}
}

void	calculate_y_step_and_side_dist(t_raycast *rc, t_game *game)
{
	if (fabs(rc->ray_dir_y) < EPSILON)
	{
		rc->step_y = 0;
		rc->side_dist_y = 0;
	}
	else if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player.y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - game->player.y) * rc->delta_dist_y;
	}
}

void	calculate_step_and_side_dist(t_raycast *rc, t_game *game)
{
	calculate_x_step_and_side_dist(rc, game);
	calculate_y_step_and_side_dist(rc, game);
}