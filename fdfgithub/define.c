/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:37:51 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/25 21:37:51 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	define_cor(t_cor *env)
{
	env->x_max = 0;
	env->y_max = 0;
	env->x = 0;
	env->y = 0;
	env->final_tab = NULL;
}

void	define_draw(t_draw *drw)
{
	drw->x0 = 0;
	drw->y0 = 0;
	drw->x1 = 0;
	drw->y1 = 0;
}

void	define_points_start(t_draw *drw, t_cor *env)
{
	drw->z0 = env->final_tab[drw->y][drw->x] * drw->scale_z;
	drw->x0 = (drw->x * scale_x(drw, env));
	drw->y0 = (drw->y * scale_y(drw, env) - env->final_tab[drw->y][drw->x]);
}
