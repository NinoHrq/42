/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:10:26 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/14 20:50:36 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//draw pixel
void	put_pixel(t_env *env, int x, int y, int color)
{
	char	*pxl;
	if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
	{
		pxl = env->addr + (y * env->mlx->line_length + \
						x * (env->mlx->bits_per_pixel / 8));
		(unsigned int *)pxl = color;
	}
}

/*Line generation algorithm*/
/*DDA Line Drawing Algorithm*/
void	draw_line(t_env *env, t_fpoint point0, t_fpoint point1)
{
	float	step;
	float	x;
	float	y;
	int		i;

	i = 0;
	env.dx = point1.x - point0.x;
	env.dy = point1.y - point0.y;
	if (fabsf(env.dx) >= fabsf(env.dy))
		step = fabsf(env.dx);
	else
		step = fabsf(env.dy);
	env.dx = env.dx / step;
	env.dy = env.dy / step;
	x = point0.x;
	y = point0.y;
	while (i < step)
	{
		put_pixel(env, -x + LARGEUR / 2 + TRANS, \
		-y + HAUTEUR / 2 + TRANS, RED);
		x = x + env.dx;
		y = y + env.dy;
		i++;
	}
}

/*draw background for the bonus*/
void	draw_background(t_env *env)
{
	int	h;
	int	w;

	h = 0;
	w = 0;
	while (h <= HAUTEUR)
	{
		w = 0;
		while (w <= LARGEUR)
		{
			put_pixel(env, w, h, BLACK);
			w++;
		}
		h++;
	}
}
