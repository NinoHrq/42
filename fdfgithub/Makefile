# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 15:59:26 by nharraqi          #+#    #+#              #
#    Updated: 2024/09/13 22:30:33 by nharraqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = start.c draw.c hooks.c fdfmain.c scale.c
OBJS    = $(SRCS:.c=.o)
NAME    = fdf
CC      = gcc -g
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror -fPIC
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

LDFLAGS = -LLibft -L./minilibx -lft -lmlx -lXext -lX11 -lGL -lm

INCLUDES = -ILibft -I./minilibx

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

${NAME}: ${OBJS}
	@make -C Libft
	@make -C minilibx
	${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}

clean:
	@make clean -C Libft
	@make clean -C minilibx
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

valgrind: ${NAME}
	valgrind $(VALGRIND_FLAGS) ./${NAME}

.PHONY: all clean fclean re valgrind Libft minilibx
