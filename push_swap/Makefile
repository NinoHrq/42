SCRS 		= instruct/push.c instruct/rrotate.c instruct/rotate.c instruct/sort_3.c\
				instruct/sort_stacks.c instruct/sort_stacks_utils.c instruct/swap.c\
				algo_stack_a.c algo_stack_b.c algo_stack_utils.c main.c parsing.c\
				parsing_utils.c split_pushswap.c stack_init.c stack_utils.c
OBJS		= $(SCRS:.c=.o)
NAME		= push_swap
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -LLibft -lft
INCLUDES	= -ILibft -Iinc

all: $(NAME)

$(NAME): $(OBJS)
	@make -C Libft
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C Libft
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re