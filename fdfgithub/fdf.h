/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:22:23 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/14 19:44:52 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_h
# define FDF_h
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

# define ANGLE 7.37
# define LARGEUR 1980
# define HAUTEUR 1080
# define ZOOM 1.1

# define SHELL_RED "\033[0;31m"
# define SHELL_YELLOW "\033[0;33m"
# define SHELL_END_COLOR "\033[m"
# define TEXT_COLOR 0x1A1A1D
# define BACKGROUND 0x1A1A1D
# define MENU_BACKGROUND 0x950740
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000

typedef struct coordinates	coord;
typedef struct bresenham	t_bre;
typedef struct draw			t_draw;
typedef struct mlx			t_mlx;

typedef struct s_ipoint {
	int	x;
	int	y;
	int	z;
}	t_ipoint;

typedef struct s_fpoint {
	float	x;
	float	y;
}	t_fpoint;

typedef struct s_delta {
	float	dx;
	float	dy;
}	t_delta;


typedef struct coordinates
{
	int						x;
	int						y;
	int						xmax;
	int						ymax;
	int						**final_tab;
	t_ipoint					*init_pts;
	t_fpoint					*final_pts;
	t_bre						*bre;
	t_mlx						*mlx;
	t_draw						*dr;
}							coord;

typedef struct bresenham
{
	int						dx;
	int						dy;
	int						sx;
	int						sy;
	int						error;
	int						e2;
}							t_bre;

typedef struct draw
{
	int						x;
	int						y;
	int						x0;
	int						y0;
	int						z0;
	int						x1;
	int						y1;
	int						z1;
	int						offset_x;
	int						offset_y;
	int						color;
	double					scl_x;
	double					scl_y;
	double					scl_z;
	coord					*env;
	t_bre					*bre;
	t_mlx					*mlx;
}							t_draw;

typedef struct mlx
{
	void					*mlx;
	void					*win;
	void					*img;
	int						line_length;
	int						bits_per_pixel;
	int						size_line;
	char					*addr;
	int						endian;
	t_draw					*dr;
	coord					*env;
}							t_mlx;
// start.c
void						map_mesure(coord *env, char *file);
void						check_matrice(coord *env, char *file);
void						put_mat_in_tab(coord *env, char *file);

// fdfmain.c
int							signal(char *message);

// draw.c
void						horizon_draw(t_draw *dr, coord *env);
void						verti_draw(t_draw *dr, coord *env);
void						iso_draw(int *x, int *y, int z);
void						calcul_draw(t_draw *dr, coord *env);
void						lines_draw(t_draw *dr, coord *env);

// scale.c
double						scale(coord *env);
double						scale_x(t_draw *dr);
double						scale_y(t_draw *dr);
void						define_env(coord *env);
void						define_draw(t_draw *dr);

// bresenham.c
void 						lilbres(t_bre *bre, t_draw *dr);
void						draw_pixel(t_mlx *mlx, int x, int y, int color);
void						bresenham(t_draw *dr);

#endif
