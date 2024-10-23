/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:58:26 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/26 02:18:36 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_cor	env;
	t_mlx	mlx;
	t_draw	drw;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./fdf map_file", 2);
		return (1);
	}
	define_cor(&env);
	define_draw(&drw);
	map_mesure(&env, av[1]);
	check_matrice(&env, av[1]);
	put_mat_in_tab(&env, av[1]);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, LARGEUR, HAUTEUR, "FDF");
	mlx.img = mlx_new_image(mlx.mlx, (LARGEUR), (HAUTEUR));
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits, &mlx.size, &mlx.endian);
	drw.mlx = &mlx;
	drw.env = &env;
	draw_lines(&drw, &env);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, (0), (0));
	manage_close(&mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
