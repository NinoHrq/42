/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:10:26 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/20 18:49:59 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(coord *env, int x, int y, int color)
{
	char	*pxl;
	unsigned int	*pxl_data;

	if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
	{
		pxl = env->mlx->addr + (y * env->mlx->line_length + x * (env->mlx->bits_per_pixel / 8));
		pxl_data = (unsigned int *)pxl;
		*pxl_data = color;
	}
}


/*DDA*/
void	draw_line(coord *env, t_fpoint point0, t_fpoint point1)
{
	float	step;
	float	x;
	float	y;
	int		i;

	i = 0;
	env->dx = point1.x - point0.x;
	env->dy = point1.y - point0.y;
	if (fabsf(env->dx) >= fabsf(env->dy))
		step = fabsf(env->dx);
	else
		step = fabsf(env->dy);
	env->dx = env->dx / step;
	env->dy = env->dy / step;
	x = point0.x;
	y = point0.y;
	while (i < step)
	{
		put_pixel(env, -x + LARGEUR / 2 + TRANS, -y + HAUTEUR / 2 + TRANS, WHITE);
		x = x + env->dx;
		y = y + env->dy;
		i++;
	}
}

/*draw background pour les bonus
void	draw_background(coord *env)
{
	int h;
	int w;

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
}*/