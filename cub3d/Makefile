# this is to manage flags for m1 architecture, we don't have to use this flag in linux
OS_ARCH 	:= $(shell uname -m)
ifeq ($(OS_ARCH),arm64)
	MLX_DIR := ./includes/minilibx_macos/
	MLX_LIB := -lmlx -framework OpenGL -framework AppKit
	OS_NAME := Mac M1
else
	MLX_DIR := ./includes/minilibx-linux/
	MLX_LIB := -lmlx -lXext -lX11
	OS_NAME := Linux
endif

# Executable name
NAME = cub3D
BONUS_NAME = cub3D_bonus

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
INC_DIR = ./includes
SRC_DIR = ./src
OBJ_DIR = ./obj
SRC_BONUS_DIR = ./src_bonus
OBJ_BONUS_DIR = ./obj_bonus

# Source files for cub3D
SRCS = main.c \
		utils.c \
		parsing1.c \
		init1.c \
		free.c \
		manage_key.c \
		raycast_1.c \
		raycast_2.c \
		utils_move_players.c \
		move_players.c \
		redraw.c \
		load_textures.c \
		p_free_utils.c \
		p_utils.c \
		p_file_extension.c \
		p_doc.c \
		p_utils2.c \
		p_value.c \
		p_value2.c \
		p_init2.c \
		p_map.c \
		p_allocate_and_wall.c \
		p_alloc.c \
		p_config.c \
		p_parse_color.c \
		p_texture_1.c \
		p_texture_2.c \
		p_inmap_and_texture.c \
		p_map_utils.c \
		p_map_ww.c \
		p_check_inner.c \
		p_player_spawn.c \
		p_file_plus.c \
		p_utils3.c \

# Source files for cub3D_bonus
BONUS_SRCS = main.c \
				key_press.c \
				manage_event.c \
				utils.c \
				free.c \
				raycast_1.c \
				raycast_2.c \
				utils_move_player.c \
				move_player.c \
				draw_map_2d_1.c \
				draw_map_2d_2.c \
				draw_map_2d_3.c \
				redraw.c \
				load_textures.c \
				p_free_utils.c \
				p_utils.c \
				p_file_extension.c \
				p_doc.c \
				p_utils2.c \
				p_value.c \
				p_value2.c \
				p_init.c \
				p_init2.c \
				p_map.c \
				p_allocate_and_wall.c \
				p_alloc.c \
				p_config.c \
				p_parse_color.c \
				p_texture_1.c \
				p_texture_2.c \
				p_inmap_and_texture.c \
				p_map_utils.c \
				p_map_ww.c \
				p_check_inner.c \
				p_player_spawn.c \
				p_file_plus.c \
				p_utils3.c \


# Object files with path prefix
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_BONUS_DIR)/, $(BONUS_SRCS:.c=.o))

# Includes directories
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Default rule
all: $(NAME)

# Rule for bonus
# bonus: re $(NAME) $(BONUS_NAME) # ???????
bonus: $(BONUS_NAME)

# Create the cub3D program
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) $(MLX_LIB) -lm -o $(NAME)

# Create the cub3D_bonus program
$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -L$(MLX_DIR) $(MLX_LIB) -lm -o $(BONUS_NAME)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile source files into object files for bonus
$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Ensure the object directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)

# Build the library (libft)
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Build the minilibx library
$(MLX):
	@$(MAKE) -s -C $(MLX_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)

# Clean object files and executable
fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(MLX_DIR) clean

# Rebuild the library and the main program
re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus