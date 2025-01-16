SRCS        = src/main.c src/main/main.c src/main/utilsmain1.c src/main/utilsmain2.c src/main/utilsmain3.c src/init.c src/builtins/exit.c src/builtins/pwd.c src/builtins/cd.c \
			src/builtins/ft_ls.c src/builtins/ft_clear.c src/builtins/ft_env.c src/builtins/ft_wc.c \
			src/builtins/ft_unset.c src/builtins/ft_export.c src/builtins/ft_echo.c
OBJ_DIR     = obj
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
NAME        = minishell
CC          = cc
RM          = rm -f
CFLAGS      = -Wall -Wextra -Werror
CPPFLAGS    = -Iinc -Isrc
LDFLAGS     = -Llibft
LDLIBS      = -lft -lreadline -lhistory

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@make clean -C libft
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
