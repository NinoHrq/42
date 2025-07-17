/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:47:26 by nharraqi          #+#    #+#             */
/*   Updated: 2025/07/17 02:20:48 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

//---------------init_get_doc.c-------------------//
char	**get_doc(char *filename);
int 	init_ctx(char *filename, t_doc *ctx);
void	initialize_context(t_doc *ctx, char *filename);
char 	**allocate_map(int size);
char 	**reallocate_map(char **map, int pre_size, int new_size);

//---------------init_get_doc2.c-------------------//
void process_line(t_doc *ctx);
void cleaning_up(t_doc *ctx);
void closing_fd(t_doc *ctx);

//---------------init_load_textures.c-------------------//
void	load_texture(t_game *game, t_texture *texture, char *path);
void	load_textures(t_game *game);
void	free_game(t_game *game);
void	free_textures_ulimit(t_game *game);
void	free_textures(t_game *game);

//---------------init1.c-------------------//
void init_game(t_game *game, char *s);
void init_player(t_game *game);
void init_textures(t_game *game);
void init_colors(t_game *game);
void init_layout(t_game *game, char *s);

//---------------init2.c-------------------//
void	init_player_pos(t_game *game);
void	init_mlx(t_game *game);
void	init_colors_int(t_game *game);
int		rgb_tab_to_int(int tab[3]);

//---------------manage_close.c-------------------//
int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);
void	manage_close(t_game *game);
int	ft_close(t_game *game);

//---------------move_player.c-------------------//
void	init_movement(t_movement *movement);
void	handle_forward_backward_movement(t_game *game, t_movement *movement);
void	move_forward_backward(t_game *game, t_movement *movement, int direction);
int	is_near_wall(t_game *game, double new_x, double new_y);
void	draw_floor_and_ceiling(t_game *game);

//---------------move_player2.c-------------------//
void	handle_left_right_movement(t_game *game, t_movement *movement);
void	move_left_right(t_game *game, t_movement *movement, int direction);
void	handle_rotation(t_game *game, t_movement *movement);
void	rotate_player(t_game *game, t_movement *movement, int direction);
void	put_pixel(t_img *img, int x, int y, int color);

//---------------p_color.c-------------------//
void	handle_color_directive(t_game *game, t_parser_context *ctx, char *line);
void parse_color(char *s,  int color[3], t_game *game);
int	parse_color_line(char *s);

//---------------p_color_utils.c-------------------//
long my_strtol(const char *str, char **endptr, int base);
void	skip_whitespace(const char **str):
int	get_sign(const char **str);
int	determine_base(const char **str, int base);
long	parse_digits(const char **str, int base, int sign, char **endptr);

//---------------p_color_utils2.c-------------------//
int	get_digit_value(char c);
int	is_valid_digit(int digit, int base);
long	update_result(t_parse_state *state, int base, int sign, char **endptr);
void	free_wrong_color(t_game *game);
void	protect_wrong_color(char **ptr, t_game *game);

//---------------p_config_utils.c-------------------//
char	*parse_doc_line(char *s);
void	handle_texture_directive(t_game *game, t_parser_context *ctx,
		char *line);
void	free_game_texture(tgame game, char *msg);

//---------------p_config.c-------------------//
void parsing_configuration(t_game *game, char **doc);
void init_parser_context(t_parser_context *ctx);
void parse_textures(t_game *game, char **doc, t_parser_context *ctx);
void	validate_textures(t_game *game, int x);
void	allocate_map(t_game *game, char **doc, int start_map, int map_size);

//---------------p_config2.c-------------------//
int	find_map_start(char **doc, int i);
int	found_end_of_the_map(char **doc);
int	tablen(char **tab);
int	calculate_map_size(char **doc, int start_map, int end_map);
int	no_empty_line(char **doc, int i, int is_map);

//---------------p_doc.c-------------------//
int	validate_identifier(char *line);
int	parse_doc(char **doc, int start_map);
void	exit_properly_parsing(t_game *game);

//---------------p_player.c-------------------//
void	process_spawn_tile(char **map, int i, int j, t_spawn_ctx *ctx);
void	process_tile(char **map, int i, int j, t_spawn_ctx *ctx);
void	check_multiple_spawns(int *d_flag, t_game *dt);
void	player_spawn(char **map, t_game *dt);

//---------------p_player2.c-------------------//
void	check_spawn_validity(char **map, int i, int j, t_game *dt);
void	carry_on(char **map, int i, int j, t_game *dt);
void	last_check_spawn(char **map, int i, int *j, t_game *dt);
void	set_player_position(char **map, int i, int j, t_game *dt);

//---------------p_textures.c-------------------//
void	assign_texture(t_game *game, t_parser_context *ctx, char c, char *doc);
void	assign_north_texture(t_game *game, char *doc);
void	assign_south_texture(t_game *game, char *doc);
void	assign_west_texture(t_game *game, char *doc);
void	assign_east_texture(t_game *game, char *doc);

//---------------p_validate_utils.c-------------------//
bool	valid_texture(t_game *game);
void	parse_texture(t_game *game);
bool	ends_with_xpm(char *path);
int	check_texture_path(const char *path);

//---------------p_wall.c-------------------//
char **parse_wall(char **map, t_game *game);
int	found_max_width(char **map);
char	**check_top_border(char **map);
char	**check_bottom_border(char **map, int map_height);
char	**check_bottom_border(char **map, int map_height);

//---------------p_wall2.c-------------------//
char	**check_first_border(char **map);
void	check_null_line(char *line, int i);
int	check_right_border(char *line, int map_width, int i);
int	check_zero_surroundings(char **map, int i, int j, int map_height);
char	**check_inner_lines(char **map, int map_height);

//---------------p_wall3.c-------------------//
int	ft_strlen_skip_empty_line(char *map);
void	free_game_wall(t_game *game);
char	**check_first_char(char **map, int map_height);

//---------------p_wall4.c-------------------//
int	is_valid_tile(char c);
int	check_up_tile(char **map, int c, int l);
int	check_down_tile(char **map, int c, int l, int map_height);
char	**check_map_validity(char **map, int map_height, int max_width);

//---------------p_wall5.c-------------------//
int	is_above_cell_valid(char **map, int c, int l);
int	is_below_cell_valid(char **map, int c, int l, int map_height);
int	is_cell_valid(char **map, int c, int l, int map_height);
char	**check_map(char **map, int map_height, int max_width);

//---------------parsing1.c-------------------//
int	parse_av(char *filename);
void verif_name(char *s);
char *extracting_extension(char *s);
int verif_extension(char *ext);

//---------------raycast.c-------------------//
void	raycast(t_game *game);
void	init_raycast(t_raycast *rc, t_game *game, int x);
void	calculate_x_step_and_side_dist(t_raycast *rc, t_game *game);
void	calculate_y_step_and_side_dist(t_raycast *rc, t_game *game);
void	calculate_step_and_side_dist(t_raycast *rc, t_game *game);

//---------------raycast2.c-------------------//
void	perform_dda(t_raycast *rc, t_game *game);
void	calculate_wall_distance_and_draw_range(t_raycast *rc, t_game *game);
void	select_texture_and_calculate_tex_coords(t_raycast *rc, t_game *game);
void	draw_wall_column(t_raycast *rc, t_game *game, int x);
void	draw_sky_and_floor_column(t_raycast *rc, t_game *game, int x);

//---------------redraw.c-------------------//
void	move_player(t_game *game);
void	draw_floor_and_ceiling(t_game *game);
void	raycast(t_game *game);
int	redraw(t_game *game);

//---------------verify_info.c-------------------//
void verify_info(t_game *game);
void free_game_texture(t_game *game, char *txt);
void	free_tab(char **tab);

#endif