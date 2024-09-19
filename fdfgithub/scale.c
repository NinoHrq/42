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

void	ddd_point(t_env *env)
{
	int	i;

	i = 0;
	env->initial_points = malloc(env->ymax * env->xmax * (sizeof(t_ipoint)));
	if (!env->initial_points)
		ft_printf("Malloc failed");
	env->y = 0;
	while (env->y < env->ymax)
	{
		env->x = 0;
		while (env->x < env->xmax)
		{
			env->initial_points[i] = (t_ipoint){env->x, env->y, \
								env->final_tab[env->y][env->x]};
			i++;
			env->x++;
		}
		env->y++;
	}
	free_final_tab(env);
}

/*Fill in the two-dimensional table*/
void	dd_point(t_env *env)
{
	int	i;

	i = 0;
	env->final_points = malloc(env->ymax * env->xmax * (sizeof(t_fpoint)));
	if (!env->final_points)
		ft_printf("Malloc failed");
	while (i < (env->xmax * env->ymax))
	{
		env->final_points[i].y = env->initial_points[i].y \
				* cosf(ANGLE) + env->initial_points[i].y \
				* cosf(ANGLE + 2) \
				+ (env->initial_points[i].z * env->altitude) \
				* cosf(ANGLE - 2);
		env->final_points[i].x = env->initial_points[i].x \
				* sinf(ANGLE) + env->initial_points[i].y \
				* sinf(ANGLE + 2) \
				+ (env->initial_points[i].z * env->altitude) \
				* sinf(ANGLE - 2);
		env->final_points[i].x *= -env->scale;
		env->final_points[i].y *= env->scale;
		i++;
	}
}
