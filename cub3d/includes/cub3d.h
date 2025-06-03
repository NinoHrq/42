/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:47:26 by nharraqi          #+#    #+#             */
/*   Updated: 2025/06/03 19:47:00 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../includes/minilibx-linux/mlx.h"
# include "../includes/minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../includes/libft/libft.h"
# include <X11/keysym.h>
# include <limits.h>
# include <time.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1010
# define BLOCK 64
# define DEBUG 2
# define TRUE 1
# define FALSE 0  

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 0xff1b
# define QUIT 17

# define PI 3.14159265358979323846
# define PLAYER_RADIUS 0.2
# define EPSILON 0.01

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define GREY 0x808080
# define RED 0xFF0000
# define GREEN 0x00FF00
# define PURPLE 0xD8BFD8

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		angle;
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			left_rotate;
	int			right_rotate;
}				t_player;

typedef struct s_texture
{
	t_img		img;
	int			width;
	int			height;

}				t_texture;

/*==========================parsing 0==================================*/

typedef struct s_parser_context
{
	int			i;
	int			j;
	int			x;
	int			start_map;
	int			end_map;
	int			map_size;
}				t_parser_context;

typedef struct s_doc
{
	int			fd;
	char		**map;
	char		*line;
	int			i;
	int			j;
	int			size;
}				t_doc;

/*==========================parsing 0==================================*/

typedef struct s_raycast
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			out_screen;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	t_texture	*texture;
}				t_raycast;

typedef struct s_movement
{
	double		move_speed;
	double		rot_speed;
	double		new_x;
	double		new_y;
	double		old_dir_x;
	double		old_plane_x;
}				t_movement;

typedef struct s_game
{
   void		*mlx;
   void		*win;
   t_img	img;
   char		*addr;
   int		bits_per_pixel;
   int		line_length;
   int		endian;
   char		player_init_direction;
   
   int		start_map;
   char		**doc;
   char		**map;
   char		*north_texture;
   char		*south_texture;
   char		*west_texture;
   char		*east_texture;
   int		index_player[2];
   char		orientation_spawn;
   int		floor_color[3];
   int		ceiling_color[3];
   int		c_color;
   int		f_color;
   t_texture	no_texture;
   t_texture	so_texture;
   t_texture	we_texture;
   t_texture	ea_texture;
   
   t_player	player;

    char **map;
} t_game;

typedef struct s_spawn_ctx
{
	t_game		*dt;
	int			d_flag;
}				t_spawn_ctx;

typedef struct s_parse_state
{
	long		result;
	int			digit;
}				t_parse_state;

//---------------parsing1.c-------------------//
int	parse_av(char *filename);
void verif_name(char *s);
char *extracting_extension(char *s);
int verif_extension(char *ext);

//---------------init1.c-------------------//
void init_game(t_game *game, char *s);
void init_player(t_game *game);
void init_textures(t_game *game);
void init_colors(t_game *game);

/*void init_player(t_player *player);
int key_release(int keycode, t_player *player);
int key_press(int keycode, t_player *player);
void move_player(t_player *player);*/
#endif