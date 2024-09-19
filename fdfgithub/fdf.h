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
# define TRANS 1
# define SCALE 30
# define ALTITUDE 0.1
# define TRANS_X 10
# define TRANS_Y 5

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000

typedef struct coordinates	coord;
typedef struct mlx		t_mlx;

typedef struct s_ipoint {
	int	x;
	int	y;
	int	z;
}	t_ipoint;

typedef struct s_fpoint {
	float	x;
	float	y;
}	t_fpoint;

typedef struct coordinates
{
	int						x;
	int						y;
	int						dx;
	int						dy;
	int						xmax;
	int						ymax;
	int						scale;
	int						translation;
	float						altitude;
	int						**final_tab;
	t_ipoint					*init_pts;
	t_fpoint					*final_pts;
	t_mlx						*mlx;
}							coord;

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
	coord					*env;
}							t_mlx;
// start.c
void						map_mesure(coord *env, char *file);
void						check_matrice(coord *env, char *file);
void						put_mat_in_tab(coord *env, char *file);
int 						ft_init(coord *env, t_mlx *mlx);
int						render(t_env *env);

// fdfmain.c
void						free_final_tab(t_env	*env);

// draw.c
void						put_pixel(t_env *env, int x, int y, int color);
void						draw_line(t_env *env, t_fpoint point0, t_fpoint point1);
void						draw_background(t_env *env);

// scale.c
void						ddd_point(t_env *env);
void						dd_point(t_env *env);

//hooks.c
void						hooks_managemt(t_env *env);
int						key_handler(int key, t_env *env);
int						close_win(t_mlx *mlx);
int						mouse_handler(int mousecode, int x, int y, t_env *env);
#endif
