/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:03:19 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/26 01:25:20 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

# define ANGLE 6.8
# define IMG_HAUTEUR_MAX 20
# define IMG_LARGEUR_MAX 20
# define EXIT 53
# define LARGEUR 1920
# define HAUTEUR 1080

// ------NOIR-----------
# define NOIR0 0xd9d9d9
# define NOIR1 0xbfbfbf
# define NOIR2 0xa6a6a6
# define NOIR3 0x8c8c8c
# define NOIR4 0x737373
# define NOIR5 0x595959
# define NOIR6 0x404040
# define NOIR7 0x262626

// ------JAUNE----------
# define JAUNE0 0xeee8aa
# define JAUNE1 0xfafad2
# define JAUNE2 0xffffe0
# define JAUNE3 0xffff00
# define JAUNE4 0xffd700
# define JAUNE5 0xeedd82
# define JAUNE6 0xdaa520
# define JAUNE7 0xb8860b

// ------ORANGE---------
# define ORANGE0 0xffe5cc
# define ORANGE1 0xffcc99
# define ORANGE2 0xffb366
# define ORANGE3 0xff9933
# define ORANGE4 0xff8000
# define ORANGE5 0xcc6600
# define ORANGE6 0x994c00
# define ORANGE7 0x663300

// ------ROUGE---------
# define ROUGE0 0xffe5e5
# define ROUGE1 0xffb3b3
# define ROUGE2 0xff8080
# define ROUGE3 0xff4d4d
# define ROUGE4 0xff1a1a
# define ROUGE5 0xe60000
# define ROUGE6 0xb30000
# define ROUGE7 0x800000

// ------ROSE----------
# define ROSE0 0xffe5e5
# define ROSE1 0xffb3b3
# define ROSE2 0xff8080
# define ROSE3 0xff4d4d
# define ROSE4 0xff1a1a
# define ROSE5 0xe60073
# define ROSE6 0xb30059
# define ROSE7 0x800040

// ------BLEU----------
# define BLEU0 0xe5f6ff
# define BLEU1 0xb3e0ff
# define BLEU2 0x80ccff
# define BLEU3 0x4db8ff
# define BLEU4 0x1aa3ff
# define BLEU5 0x007acc
# define BLEU6 0x005999
# define BLEU7 0x003366

// ------VERT----------
# define VERT0 0xe5ffe5
# define VERT1 0xb3ffb3
# define VERT2 0x80ff80
# define VERT3 0x4dff4d
# define VERT4 0x1aff1a
# define VERT5 0x00cc00
# define VERT6 0x009900
# define VERT7 0x006600

// ------BEIGE---------
# define BEIGE0 0xf5f5dc
# define BEIGE1 0xe8cba2
# define BEIGE2 0xd2b48c
# define BEIGE3 0xdeb887
# define BEIGE4 0xc2b280
# define BEIGE5 0xbda16b
# define BEIGE6 0xb39f8e
# define BEIGE7 0x9e7e6d

typedef struct coordinates	t_cor;
typedef struct bresenham	t_bre;
typedef struct draw			t_draw;
typedef struct mlx			t_mlx;

typedef struct coordinates
{
	int						x;
	int						y;
	int						z;
	int						x_max;
	int						y_max;
	int						**final_tab;
}							t_cor;

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
	double					scale_x;
	double					scale_y;
	double					scale_z;
	t_cor					*env;
	t_bre					*bre;
	t_mlx					*mlx;
}							t_draw;

typedef struct mlx
{
	void					*mlx;
	void					*win;
	void					*img;
	int						line_length;
	int						bits;
	int						size;
	char					*addr;
	int						endian;
	t_draw					*drw;
	t_cor					*env;
}							t_mlx;

// start.c
void						map_mesure(t_cor *env, char *file);
void						check_matrice(t_cor *env, char *file);
void						put_mat_in_tab(t_cor *env, char *file);
int							error(char *error_message);
void						free_all(t_cor *env);

// draw.c
void						draw_horizontale(t_draw drw, t_cor *env);
void						draw_verticale(t_draw drw, t_cor *env);
void						draw_calcul(t_draw drw, t_cor *env);
void						draw_lines(t_draw *drw, t_cor *env);
void						draw_isometrique(int *x, int *y, int z);

// scale.c
double						ft_scale(t_cor *env);
double						scale_x(t_draw *drw, t_cor *env);
double						scale_y(t_draw *drw, t_cor *env);

// bresenham.c
void						little_bresenham(t_bre *bre, t_draw *drw);
void						bresenham(t_draw *drw);

// pixel_and_color.c
void						draw_pixel(t_mlx *mlx, int x, int y, int z);
unsigned int				color_pxl(int z);
unsigned int				noir(int z);
unsigned int				bleu(int z);
unsigned int				vert(int z);

// color.c
unsigned int				rose(int z);
unsigned int				rouge(int z);
unsigned int				orange(int z);
unsigned int				jaune(int z);
unsigned int				beige(int z);

// define.c
void						define_cor(t_cor *env);
void						define_draw(t_draw *drw);
void						define_points_start(t_draw *drw, t_cor *env);

// hook.c
int							ft_close(t_mlx *mlx);
int							key_handler(int key, t_mlx *mlx);
void						manage_close(t_mlx *mlx);

#endif
