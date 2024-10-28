#include "list.h"
#include <stdlib.h>

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int tmp;
	t_list *start;

	start = lst;

	while(lst != NULL && lst->next != NULL)
	{
		if (cmp(lst->data, lest->next->data) == 0)
		{
			tmp = lst->data;
			lst->data = lst->next->data;
			lst->next->data = tmp;
		}
		else
			lst = lst->next;
	}
	return(start);
}