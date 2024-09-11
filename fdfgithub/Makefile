# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 15:59:26 by nharraqi          #+#    #+#              #
#    Updated: 2024/09/11 16:27:35 by nharraqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = start.c draw.c bresenham.c fdf.c
OBJS    = $(SRCS:.c=.o)
NAME    = fdf
CC      = gcc -g
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror -fPIC
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

LDFLAGS = -Llibft -L./minilibx -lft -lmlx -lXext -lX11 -lGL -lm -lFt_printf

INCLUDES = -Ilibft -I./minilibx -IFt_printf

all: ${NAME}

%.o: %.c
    ${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

${NAME}: ${OBJS}
    @make -C libft
    @make -C minilibx
	@make clean -C Ft_printf
    ${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}

clean:
    @make clean -C libft
    @make clean -C minilibx
	@make clean -C Ft_printf
    ${RM} ${OBJS}

fclean: clean
    ${RM} ${NAME}

re: fclean all

valgrind: ${NAME}
    valgrind $(VALGRIND_FLAGS) ./${NAME}

.PHONY: all clean fclean re valgrind Libft Ft_printf minilibx