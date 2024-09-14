/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:16:49 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/14 19:40:48 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	scale(coord *env)
{
	double	diffz;

	diffz = (double)HAUTEUR / (env->ymax + env->xmax);
	return (diffz);
}

double	scale_x(t_draw *dr)
{
	dr->scl_x = (double)SCL_LARGEUR / 40;
	return (dr->scl_x);
}

double	scale_y(t_draw *dr)
{
	dr->scl_y = (double)SCL_HAUTEUR / 40;
	return (dr->scl_y);
}

void	define_env(coord *env)
{
	env->xmax = 0;
	env->ymax = 0;
	env->x = 0;
	env->y = 0;
	env->final_tab = NULL;
}
void	define_draw(t_draw *dr)
{
	dr->x0 = 0;
	dr->y0 = 0;
	dr->x1 = 0;
	dr->y1 = 0;
}