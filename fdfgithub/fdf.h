/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:22:23 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/11 17:25:36 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_h
# define FDF_h
# include "ft_printf.h"
# include "libft.h"
# include "mlx_int.h"
# include <fcnt1.h>
# include <math.h>
# include <stdlib.h>

# define ANGLE 7.37

typedef struct draw
{
	int		x;
	int		y;
	int		x0;
	int		y0;
	int		z0;
	int		x1;
	int		y1;
	int		z1;
	int		color;
}			t_draw;

typedef struct coordinates
{
	int		x;
	int		y;
	int		xmax;
	int		ymax;
	int		**final_tab;
}			coord;

// start.c
void		map_mesure(coord *env, char *file);
void		check_matrice(coord *env, char *file);
void		put_mat_in_tab(coord *env, char *file);

// fdf.c
int			signal(char *message);

// draw.c
void		horizon_draw(t_draw *dr, coord *env);
void		verti_draw(t_draw *dr, coord *env);
void		iso_draw(int *x, int *y, int z);
void		calcul_draw(t_draw *dr, coord *env);
void		lines_draw(t_draw *dr, coord *env);