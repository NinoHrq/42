/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:01:46 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/14 19:41:06 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	coord	env;
	t_mlx	mlx;
	
	env.translation = 1;
	env.scale = 30;
	env.altitude = 1;
	env.y = 0;
	env.ymax = 0;
	env.xmax = 0;
	if (argc == 2)
	{
		map_mesure(&env, argv[1]);
		check_matrice(&env, argv[1]);
		put_mat_in_tab(&env, argv[1]);
		ddd_point(&env);
		ft_init(&env, &mlx);
	}
	else
		ft_printf("Wrong number of args");
	while (1)
		;
}

void	free_final_tab(t_env	*env)
{
	int	y;

	y = 0;
	while (y < env->map_h)
	{
		free(env->final_tab[y]);
		y++;
	}
	free(env->final_tab);
}
