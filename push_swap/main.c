/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:00:53 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/08 23:01:56 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_av(char **av)
{
	int	i;

	if (av == NULL)
		return ;
	i = 0;
	while (av[i])
	{
		if (av[i] != NULL)
		{
			free(av[i]);
		}
		i++;
	}
	free(av);
	return ;
}

static void	clear_end_of_main(int ac, char **av, t_stack_node *a)
{
	if (ac == 2)
		free_av(av);
	free_stack(&a);
}

static void	for_norminette(t_stack_node **a, t_stack_node **b)
{
	if (stack_len(*a) == 2)
		sa(a);
	else if (stack_len(*a) == 3)
		sort_3(a);
	else
		sort_stacks(a, b);
}

int	main(int ac, char **av)
{
	t_stack_node	*a;
	t_stack_node	*b;

	a = NULL;
	b = NULL;
	if (ac == 1)
		return (1);
	else if (ac == 2)
	{
		if (av[1][0] == '\0')
			return (1);
		av = split_for_push_swap(av[1]);
		init_stack_a_for_split(&a, av);
	}
	else
		init_stack_a(&a, av + 1);
	if (!stack_sorted(a))
		for_norminette(&a, &b);
	clear_end_of_main(ac, av, a);
	return (0);
}