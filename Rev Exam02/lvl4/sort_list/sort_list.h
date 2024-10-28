#ifndef LIST_H
# define LIST_H

typedef struct s_list;

struct					s_list
{
	int					data;
	s_list				*next;
}						t_list;

# endif

