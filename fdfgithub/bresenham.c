/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:22:19 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/25 22:18:32 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham(t_draw *drw)
{
	drw->bre = malloc(sizeof(t_bre));
	if (!drw->bre)
		return ;
	little_bresenham(drw->bre, drw);
	while (1)
	{
		draw_pixel(drw->mlx, drw->x0, drw->y0, drw->z0);
		if (drw->x0 == drw->x1 && drw->y0 == drw->y1)
			break ;
		drw->bre->e2 = 2 * drw->bre->error;
		if (drw->bre->e2 > -drw->bre->dy)
		{
			drw->bre->error -= drw->bre->dy;
			drw->x0 += drw->bre->sx;
		}
		if (drw->bre->e2 < drw->bre->dx)
		{
			drw->bre->error += drw->bre->dx;
			drw->y0 += drw->bre->sy;
		}
	}
	free(drw->bre);
}

void	little_bresenham(t_bre *bre, t_draw *drw)
{
	bre->dx = abs(drw->x1 - drw->x0);
	bre->dy = abs(drw->y1 - drw->y0);
	if (drw->x0 < drw->x1)
		bre->sx = 1;
	else
		bre->sx = -1;
	if (drw->y0 < drw->y1)
		bre->sy = 1;
	else
		bre->sy = -1;
	bre->error = bre->dx - bre->dy;
}
