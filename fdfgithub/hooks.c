/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:24:57 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/20 17:47:02 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hooks_managemt(coord *env)
{
	mlx_key_hook(env->mlx->win, key_handler, env);
	mlx_hook(env->mlx->win, 17, 0, close_win, env);
	mlx_hook(env->mlx->win, 4, 0, mouse_handler, env);
	mlx_hook(env->mlx->win, 2, 1L << 0, key_handler, env);
}

int	key_handler(int key, coord *env)
{
	if (key == 53)
		close_win(env->mlx);
	else if (key == 13 || key == 126)
		env->translation -= TRANS_X;
	else if (key == 1 || key == 125)
		env->translation += TRANS_X;
	else if (key == 0 || key == 123)
		env->angle += 0.01;
	else if (key == 2 || key == 124)
		env->angle -= 0.01;
	else if (key == 6)
		env->altitude += ALTITUDE;
	else if (key == 7)
		env->altitude -= ALTITUDE;
	return (0);
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	mouse_handler(int mousecode, int x, int y, coord *env)
{
	(void)x;
	(void)y;
	if (mousecode == 4)
		env->scale *= ZOOM;
	else if (mousecode == 5)
		env->scale /= ZOOM;
	return (0);
}