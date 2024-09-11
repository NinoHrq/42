/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:10:26 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/10 17:22:43 by nharraqi         ###   ########.fr       */
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
	*y = (tmp_x + tmp_y) * sin(ANGLE) - z;
	ft_printf("Transformation Isometric: (%d, %d, %d) -> (%d, %d)\n", tmp_x,
		tmp_y, z, *x, *y);
}

void	calcul_draw(t_draw *dr, coord *env)
{
	dr->y = 0;
	while (dr->y < env->ymax)
	{
		dr->x = 0;
		while (dr->x < env->xmax)
		{
			dr->z0 = env->final_tab[dr->y][dr->x];
			dr->x0 = dr->x * 10;
			dr->y0 = dr->y * 10 - env->final_tab[dr->y][dr->x];
			iso_draw(&dr->x0, &dr->y0, dr->z0);
			ft_printf("Dessin du point de coordonnees (%d, %d)\n", dr->x0,
				dr->y0);
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
	dr->z1 = env->final_tab[dr->y + 1][dr->x];
	dr->x1 = dr->x * 10;
	dr->y1 = (dr->y + 1) * 10 - env->final_tab[dr->y + 1][dr->x];
	iso_draw(&dr->x1, &dr->y1, dr->z1);
	ft_printf("Dessin de la ligne vertical de (%d, %d) to (%d, %d)\n", dr->x0,
		dr->y0, dr->x1, dr->y1);
	bresenham(dr);
}

void	horizon_draw(t_draw *dr, coord *env)
{
	dr->z1 = env->final_tab[dr->y][dr->x + 1];
	dr->x1 = (dr->x + 1) * 10;
	dr->y1 = dr->y * 10 - env->final_tab[dr->y][dr->x + 1];
	iso_draw(&dr->x1, &dr->y1, dr->z1);
	ft_printf("Dessin de la ligne horizontal de (%d, %d) to (%d, %d)\n", dr->x0,
		dr->y0, dr->x1, dr->y1);
	bresenham(dr);
}

void	lines_draw(t_draw *dr, coord *env)
{
	calcul_draw(dr, env);
	ft_putendl_fd("Dessin completement complet!", 1);
}