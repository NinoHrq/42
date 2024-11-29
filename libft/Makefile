NAME    = libft.a
CFLAGS    = -Wall -Wextra -Werror -fPIC
OBJS    = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
    ft_strlen.o ft_toupper.o ft_tolower.o ft_strlcpy.o ft_strlcat.o ft_strncmp.o \
    ft_atoi.o ft_strchr.o ft_strrchr.o ft_strnstr.o ft_memcmp.o ft_memchr.o ft_memset.o \
    ft_bzero.o ft_memcpy.o  ft_memmove.o ft_strdup.o ft_calloc.o ft_strjoin.o ft_split.o \
    ft_itoa.o ft_substr.o ft_strtrim.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o \
    ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_put_x.o ft_put_u.o \
    ft_put_p.o ft_put_s.o ft_put_d_i.o ft_put_c.o ft_check_type.o ft_printf.o \
    get_next_line.o

OBJSB = ft_lstnew.o ft_lstsize.o ft_lstadd_back.o ft_lstlast.o ft_lstiter.o \
    ft_lstdelone.o ft_lstclear.o ft_lstadd_front.o \

SRCS    = $(OBJS:.o=.c)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar crs $(NAME) $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	cc $(CFLAGS) -c $< -o $@ -I./

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: ${NAME} ${OBJSB}
	ar crs ${NAME} ${OBJSB}
