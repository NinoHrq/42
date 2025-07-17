/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:42:11 by nharraqi          #+#    #+#             */
/*   Updated: 2025/07/17 00:56:43 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_game game;
    
    if(ac == 2)
    {
        if (parse_av(av[1]) == 0)
        {
            init_game(&game, av[1]);
            if(game.map)
            {
                manage_close(&game);
                mlx_loop_hook(game.mlx, redraw, &game);
                mlx_loop(game.mlx);
                free_tab(game.map);
            }
        }
        else
           printf("\n\n\tUSAGE : \"./cub3D\" \"file.cub\"\n\n\n"); 
    }
    else
        printf("\n\n\tUSAGE : \"./cub3D\" \"file.cub\"\n\n\n");
	return (0);
}