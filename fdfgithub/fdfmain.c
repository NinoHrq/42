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

int	main(int ac, char **av)
{
	coord env;
	t_mlx mlx;
	t_draw dr;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./fdf map_file", 2);
		return (1);
	}

	// Initialiser les structures
	define_env(&env);
	define_draw(&dr);
	map_mesure(&env, av[1]);
	check_matrice(&env, av[1]);
	put_mat_in_tab(&env, av[1]);

	// Initialisation de mlx
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, LARGEUR, HAUTEUR, "FDF");
	mlx.img = mlx_new_image(mlx.mlx, LARGEUR, HAUTEUR);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.size_line,
			&mlx.endian);
	// Initialiser la structure de dessin
	dr.mlx = &mlx;
	dr.env = &env;

	// Dessiner les lignes de la matrice avec Bresenham en vue isométrique
	lines_draw(&dr, &env);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);

	// Libération de la mémoire
	int i;
	for (i = 0; i < env.ymax; i++)
	{
		free(env.final_tab[i]);
	}
	free(env.final_tab);
	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);

	return (0);
}