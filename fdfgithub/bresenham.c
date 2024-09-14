/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:22:19 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/10 16:44:47 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	lilbres(t_bre *bre, t_draw *dr);

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *pxl;
	// Vérifier que les coordonnées sont dans les limites de l'image
	if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
	{
		// Calculer l'adresse du pixel dans l'image
		pxl = mlx->addr + (y * mlx->size_line + x * (mlx->bits_per_pixel / 8));
		// Écrire la couleur dans l'adresse du pixel
		*(unsigned int *)pxl = color;
	}
}
void	bresenham(t_draw *dr)
{
	dr->color = 0xFFFFFF;
	dr->bre = malloc(sizeof(t_bre));
	if (!dr->bre)
		return ;
	lilbres(dr->bre, dr);
	while (1)
	{
		//mlx_pixel_put(dr->mlx->mlx, dr->mlx->win, dr->x0, dr->y0, dr->color);
		draw_pixel(dr->mlx, dr->x0, dr->y0, dr->color);
		if (dr->x0 == dr->x1 && dr->y0 == dr->y1)
			break ;
		dr->bre->e2 = 2 * dr->bre->error;
		if (dr->bre->e2 > -dr->bre->dy)
		{
			dr->bre->error -= dr->bre->dy;
			dr->x0 += dr->bre->sx;
		}
		if (dr->bre->e2 < dr->bre->dx)
		{
			dr->bre->error += dr->bre->dx;
			dr->y0 += dr->bre->sy;
		}
	}
	free(dr->bre);
}

void	lilbres(t_bre *bre, t_draw *dr)
{
	bre->dx = abs(dr->x1 - dr->x0);
	bre->dy = abs(dr->y1 - dr->y0);
	if (dr->x0 < dr->x1)
		bre->sx = 1;
	else
		bre->sx = -1;
	if (dr->y0 < dr->y1)
		bre->sy = 1;
	else
		bre->sy = -1;
	bre->error = bre->dx - bre->dy;
}