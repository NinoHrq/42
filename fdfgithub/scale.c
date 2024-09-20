/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:16:49 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/20 17:59:16 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ddd_point(coord *env)
{
	int	i;

	i = 0;
	env->init_pts = malloc(env->ymax * env->xmax * (sizeof(t_ipoint)));
	if (!env->init_pts)
		ft_printf("Malloc failed");
	env->y = 0;
	while (env->y < env->ymax)
	{
		env->x = 0;
		while (env->x < env->xmax)
		{
			env->init_pts[i] = (t_ipoint){env->x, env->y,
				env->final_tab[env->y][env->x]};
			i++;
			env->x++;
		}
		env->y++;
	}
	free_final_tab(env);
}

/*Fill in the two-dimensional table*/
void	dd_point(coord *env)
{
	int i;

	i = 0;
	env->final_pts = malloc(env->ymax * env->xmax * (sizeof(t_fpoint)));
	if (!env->final_pts)
		ft_printf("Malloc fail");
	while (i < (env->xmax * env->ymax))
	{
		env->final_pts[i].y = env->init_pts[i].y * cosf(env->angle)
			+ env->init_pts[i].y * cosf(env->angle + 2) + (env->init_pts[i].z
				* env->altitude) * cosf(env->angle - 2);
		env->final_pts[i].x = env->init_pts[i].x * sinf(env->angle)
			+ env->init_pts[i].y * sinf(env->angle + 2) + (env->init_pts[i].z
				* env->altitude) * sinf(env->angle - 2);
		env->final_pts[i].x *= -env->scale;
		env->final_pts[i].y *= env->scale;
		i++;
	}
}