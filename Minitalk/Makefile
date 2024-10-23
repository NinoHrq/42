SRCS    = client.c server.c
OBJS    = $(SRCS:.c=.o)
SERVER	= server
CLIENT	= client
CC      = cc -g
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror

LDFLAGS = -LLibft -lft

INCLUDES = -ILibft

all: ${SERVER} ${CLIENT}


$(SERVER): server.o
	@make -C Libft
	$(CC) $(CFLAGS) server.o $(LDFLAGS) -o $(SERVER)

$(CLIENT): client.o
	@make -C Libft
	$(CC) $(CFLAGS) client.o $(LDFLAGS) -o $(CLIENT)

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	@make clean -C Libft
	${RM} ${OBJS}

fclean: clean
	${RM} ${SERVER} ${CLIENT}

re: fclean all

.PHONY: all clean fclean re