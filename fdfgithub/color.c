/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:19:09 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/25 22:19:09 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	rose(int z)
{
	unsigned int	c;

	if (z > 140 && z <= 150)
		c = ROSE0;
	else if (z > 150 && z <= 160)
		c = ROSE1;
	else if (z > 160 && z <= 170)
		c = ROSE2;
	else if (z > 170 && z <= 180)
		c = ROSE3;
	else if (z > 180 && z <= 190)
		c = ROSE4;
	else if (z > 190 && z <= 200)
		c = ROSE5;
	else if (z > 200 && z <= 210)
		c = ROSE6;
	else if (z > 210 && z <= 220)
		c = ROSE7;
	return (c);
}

unsigned int	rouge(int z)
{
	unsigned int	c;

	if (z > 220 && z <= 230)
		c = ROUGE0;
	else if (z > 230 && z <= 240)
		c = ROUGE1;
	else if (z > 240 && z <= 250)
		c = ROUGE2;
	else if (z > 250 && z <= 260)
		c = ROUGE3;
	else if (z > 260 && z <= 270)
		c = ROUGE4;
	else if (z > 270 && z <= 280)
		c = ROUGE5;
	else if (z > 280 && z <= 290)
		c = ROUGE6;
	else if (z > 290 && z <= 300)
		c = ROUGE7;
	return (c);
}

unsigned int	orange(int z)
{
	unsigned int	c;

	if (z > 300 && z <= 310)
		c = ORANGE0;
	else if (z > 310 && z <= 320)
		c = ORANGE1;
	else if (z > 320 && z <= 330)
		c = ORANGE2;
	else if (z > 330 && z <= 340)
		c = ORANGE3;
	else if (z > 340 && z <= 350)
		c = ORANGE4;
	else if (z > 350 && z <= 360)
		c = ORANGE5;
	else if (z > 360 && z <= 370)
		c = ORANGE6;
	else if (z > 370 && z <= 380)
		c = ORANGE7;
	return (c);
}

unsigned int	jaune(int z)
{
	unsigned int	c;

	if (z > 380 && z <= 390)
		c = JAUNE0;
	else if (z > 390 && z <= 400)
		c = JAUNE1;
	else if (z > 400 && z <= 410)
		c = JAUNE2;
	else if (z > 410 && z <= 420)
		c = JAUNE3;
	else if (z > 420 && z <= 430)
		c = JAUNE4;
	else if (z > 430 && z <= 440)
		c = JAUNE5;
	else if (z > 440 && z <= 450)
		c = JAUNE6;
	else if (z > 450 && z <= 460)
		c = JAUNE7;
	return (c);
}

unsigned int	beige(int z)
{
	unsigned int	c;

	if (z > 460 && z <= 470)
		c = BEIGE0;
	else if (z > 470 && z <= 480)
		c = BEIGE1;
	else if (z > 480 && z <= 490)
		c = BEIGE2;
	else if (z > 490 && z <= 500)
		c = BEIGE3;
	else if (z > 500 && z <= 510)
		c = BEIGE4;
	else if (z > 510 && z <= 520)
		c = BEIGE5;
	else if (z > 520 && z <= 530)
		c = BEIGE6;
	else if (z > 530 && z <= 540)
		c = BEIGE7;
	return (c);
}
