# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 15:05:35 by nharraqi          #+#    #+#              #
#    Updated: 2024/09/18 15:12:17 by nharraqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
CFLAGS    = -Wall -Wextra -Werror -fPIE
OBJS    = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
    ft_strlen.o ft_toupper.o ft_tolower.o ft_strlcpy.o ft_strlcat.o ft_strncmp.o \
    ft_atoi.o ft_strchr.o ft_strrchr.o ft_strnstr.o ft_memcmp.o ft_memchr.o ft_memset.o \
    ft_bzero.o ft_memcpy.o ft_memmove.o ft_strdup.o ft_calloc.o ft_strjoin.o \
    ft_itoa.o ft_substr.o ft_strtrim.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o \
    ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_split.o get_next_line.o \
	ft_printf.o ft_printhexa_maj.o ft_printhexa_min.o ft_ptrhexa.o ft_putnbr_base.o \
	ft_putnbr.o ft_putnbru.o ft_putchar.o ft_putstr.o\

OBJSB = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstdelone.o \
	ft_lstclear.o ft_lstiter.o ft_lstadd_back.o \

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
	
