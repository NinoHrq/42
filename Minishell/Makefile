NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iinc -Isrc
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft -lreadline -lhistory
SRCS = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)

	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)

	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

