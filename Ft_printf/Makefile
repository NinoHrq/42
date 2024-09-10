NAME    = libftprintf.a 
CFLAGS    = -Wall -Wextra -Werror
OBJS    = ft_printf.o ft_printhexa_maj.o ft_printhexa_min.o ft_ptrhexa.o \
ft_putchar.o ft_putnbr_base.o ft_putnbr.o ft_putnbru.o ft_putstr.o ft_strchr.o 

SRCS    = $(OBJS:.o=.c)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar crs $(NAME) $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	cc $(CFLAGS) -c $< -o $@ -I./

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
