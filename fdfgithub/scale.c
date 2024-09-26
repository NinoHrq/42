/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:37:06 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/25 21:49:12 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_scale(t_cor *env)
{
	double	h;

	h = ((double)HAUTEUR / (env->y_max + env->x_max));
	return (h);
}

double	scale_x(t_draw *drw, t_cor *env)
{
	drw->scale_x = ((double)LARGEUR / (env->x_max));
	return (drw->scale_x);
}

double	scale_y(t_draw *drw, t_cor *env)
{
	drw->scale_y = ((double)HAUTEUR / (env->y_max));
	return (drw->scale_y);
}
