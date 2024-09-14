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

void	horizon_draw(t_draw *dr, coord *env);
void	verti_draw(t_draw *dr, coord *env);

void	iso_draw(int *x, int *y, int z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = (tmp_x - tmp_y) * cos(ANGLE);
	*y = (((tmp_x + tmp_y) * sin(ANGLE)) - z);
}

void	calcul_draw(t_draw *dr, coord *env)
{
	dr->scl_z = scale(env);
	dr->y = 0;
	dr->offset_x = (int)LARGEUR / 2;
	dr->offset_y = (int)HAUTEUR / 2;
	while (dr->y < env->ymax)
	{
		dr->x = 0;
		while (dr->x < env->xmax)
		{
			dr->z0 = env->final_tab[dr->y][dr->x] * dr->scl_z;
			dr->x0 = dr->x * scale_x(dr) + dr->offset_x;
			dr->y0 = dr->y * scale_y(dr) - env->final_tab[dr->y][dr->x]
				+ dr->offset_y;
			iso_draw(&dr->x0, &dr->y0, dr->z0);
			if (dr->x + 1 < env->xmax)
				horizon_draw(dr, env);
			if (dr->y + 1 < env->ymax)
				verti_draw(dr, env);
			dr->x++;
		}
		dr->y++;
	}
}

void	verti_draw(t_draw *dr, coord *env)
{
	dr->offset_x = (LARGEUR - (env->xmax * 20)) / 2;
	dr->offset_y = (HAUTEUR - (env->ymax * 20)) / 2;
	dr->scl_z = scale(env);
	dr->z1 = env->final_tab[dr->y + 1][dr->x] * dr->scl_z;
	dr->x1 = dr->x * scale_x(dr) + dr->offset_x;
	dr->y1 = ((dr->y + 1) * scale_y(dr) - env->final_tab[dr->y + 1][dr->x]) + dr->offset_y;
	iso_draw(&dr->x1, &dr->y1, dr->z1);
	bresenham(dr);
}

void	horizon_draw(t_draw *dr, coord *env)
{
	dr->offset_x = (LARGEUR - (env->xmax * 20)) / 2;
	dr->offset_y = (HAUTEUR - (env->ymax * 20)) / 2;
	dr->scl_z = scale(env);
	dr->z1 = env->final_tab[dr->y][dr->x + 1] * dr->scl_z;
	dr->x1 = (dr->x + 1) * scale_x(dr) + dr->offset_x;
	dr->y1 = (dr->y * scale_y(dr) - env->final_tab[dr->y][dr->x + 1]) + dr->offset_y;
	iso_draw(&dr->x1, &dr->y1, dr->z1);
	bresenham(dr);
}

void	lines_draw(t_draw *dr, coord *env)
{
	calcul_draw(dr, env);
	ft_putendl_fd("Dessin completement complet!", 1);
}