/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_and_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:33:30 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/25 21:33:30 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int z)
{
	char			*pxl;
	unsigned int	color;

	if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
	{
		pxl = mlx->addr + (y * mlx->size + x * (mlx->bits / 8));
		color = color_pxl(z);
		*(unsigned int *)pxl = color;
	}
}

unsigned int	color_pxl(int z)
{
	unsigned int	color_value;

	if (z <= -20 && z >= -100)
		color_value = noir(z);
	else if (z > -20 && z <= 60)
		color_value = bleu(z);
	else if (z > 60 && z <= 140)
		color_value = vert(z);
	else if (z > 140 && z <= 220)
		color_value = rose(z);
	else if (z > 220 && z <= 300)
		color_value = rouge(z);
	else if (z > 300 && z <= 380)
		color_value = orange(z);
	else if (z > 380 && z <= 460)
		color_value = jaune(z);
	else if (z > 460 && z <= 540)
		color_value = beige(z);
	else
		color_value = 0xffffe0;
	return (color_value);
}

unsigned int	noir(int z)
{
	unsigned int	c;

	if (z >= -100 && z <= -90)
		c = NOIR0;
	else if (z > -90 && z <= -80)
		c = NOIR1;
	else if (z > -80 && z <= -70)
		c = NOIR2;
	else if (z > -70 && z <= -60)
		c = NOIR3;
	else if (z > -60 && z <= -50)
		c = NOIR4;
	else if (z > -50 && z <= -40)
		c = NOIR5;
	else if (z > -40 && z <= -30)
		c = NOIR6;
	else if (z > -30 && z <= -20)
		c = NOIR7;
	return (c);
}

unsigned int	bleu(int z)
{
	unsigned int	c;

	if (z > -20 && z <= -10)
		c = BLEU0;
	else if (z > -10 && z <= 0)
		c = BLEU1;
	else if (z > 0 && z <= 10)
		c = BLEU2;
	else if (z > 10 && z <= 20)
		c = BLEU3;
	else if (z > 20 && z <= 30)
		c = BLEU4;
	else if (z > 30 && z <= 40)
		c = BLEU5;
	else if (z > 40 && z <= 50)
		c = BLEU6;
	else if (z > 50 && z <= 60)
		c = BLEU7;
	return (c);
}

unsigned int	vert(int z)
{
	unsigned int	c;

	if (z > 60 && z <= 70)
		c = VERT0;
	else if (z > 70 && z <= 80)
		c = VERT1;
	else if (z > 80 && z <= 90)
		c = VERT2;
	else if (z > 90 && z <= 100)
		c = VERT3;
	else if (z > 100 && z <= 110)
		c = VERT4;
	else if (z > 110 && z <= 120)
		c = VERT5;
	else if (z > 120 && z <= 130)
		c = VERT6;
	else if (z > 130 && z <= 140)
		c = VERT7;
	return (c);
}
