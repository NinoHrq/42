/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/25 21:36:26 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/25 21:36:26 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

int	key_handler(int key, t_mlx *mlx)
{
	if (key == 65307 || key == 17)
		ft_close(mlx);
	return (0);
}

void	manage_close(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key_handler, mlx);
	mlx_hook(mlx->win, 17, 65307, ft_close, mlx);
}
