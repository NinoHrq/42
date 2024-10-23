SRCS    = start.c draw.c main.c scale.c pixel_and_color.c hook.c define.c color.c bresenham.c 
OBJS    = $(SRCS:.c=.o)
NAME    = fdf
CC      = gcc -g
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror -fPIC

LDFLAGS = -LLibft -L./minilibx-linux -lft -lmlx -lXext -lX11 -lGL -lm

INCLUDES = -ILibft -I./minilibx-linux

all: minilibx-linux ${NAME} 

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

${NAME}: ${OBJS}
	@make -C Libft
	@make -C minilibx-linux
	${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}

clean:
	@make clean -C Libft
	@make clean -C minilibx-linux
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

minilibx-linux:
	git clone https://github.com/42Paris/minilibx-linux.git $@

re: fclean all


.PHONY: all clean fclean re valgrind Libft minilibx-linux

