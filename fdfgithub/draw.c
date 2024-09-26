/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:10:26 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/26 02:23:26 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_lines(t_draw *drw, t_cor *env)
{
	draw_calcul(*drw, env);
	ft_putendl_fd("Dessin complet!", 1);
}

void	draw_calcul(t_draw drw, t_cor *env)
{
	drw.scale_z = ft_scale(env);
	drw.y = -1;
	while (++drw.y < env->y_max)
	{
		drw.x = -1;
		while (++drw.x < env->x_max)
		{
			define_points_start(&drw, env);
			draw_isometrique(&drw.x0, &drw.y0, drw.z0);
			if (drw.x + 1 < env->x_max)
			{
				draw_horizontale(drw, env);
			}
			if (drw.y + 1 < env->y_max)
			{
				draw_verticale(drw, env);
			}
		}
	}
	free_all(env);
}

void	draw_verticale(t_draw drw, t_cor *env)
{
	drw.z1 = (env->final_tab[drw.y + 1][drw.x]) * (drw.scale_z);
	drw.x1 = ((drw.x)) * (scale_x(&drw, env));
	drw.y1 = (((drw.y + 1) * scale_y(&drw, env) - env->final_tab
			[drw.y + 1][drw.x]));
	draw_isometrique(&drw.x1, &drw.y1, drw.z1);
	bresenham(&drw);
}

void	draw_horizontale(t_draw drw, t_cor *env)
{
	drw.z1 = (env->final_tab[drw.y][drw.x + 1]) * (drw.scale_z);
	drw.x1 = ((drw.x +1)) * scale_x(&drw, env);
	drw.y1 = (((drw.y) * scale_y(&drw, env) - env->final_tab
			[drw.y][drw.x + 1]));
	draw_isometrique(&drw.x1, &drw.y1, drw.z1);
	bresenham(&drw);
}

void	draw_isometrique(int *x, int *y, int z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = (LARGEUR / 2.5) + (tmp_x - tmp_y) * cos(ANGLE) / 2.81;
	*y = (HAUTEUR / 2.81) + (((tmp_x + tmp_y) * sin(ANGLE)) - z) / 3;
}
