/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:11:07 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/08 23:11:09 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_node_value(t_stack_node *node, int n)
{
	node->next = NULL;
	node->nb = n;
	node->index = 0;
	node->push_cost = 0;
	node->median = 0;
	node->cheapest = 0;
	node->target = NULL;
}

static void	append_node(t_stack_node **stack, int n)
{
	t_stack_node	*node;
	t_stack_node	*last_node;

	if (!stack)
		return ;
	node = malloc(sizeof(t_stack_node));
	if (!node)
		return ;
	init_node_value(node, n);
	if (!(*stack))
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
}

void	init_stack_a(t_stack_node **a, char **av)
{
	long	n;
	int		i;

	i = 0;
	while (av[i])
	{
		n = ft_atol(av[i], a);
		if (check_double(*a, (int)n))
			free_errors(a);
		append_node(a, (int)n);
		i++;
	}
}

void	init_stack_a_for_split(t_stack_node **a, char **av)
{
	long	n;
	int		i;

	i = 0;
	while (av[i])
	{
		n = ft_atol_for_split(av[i], a, av);
		if (check_double(*a, (int)n))
			free_errors_for_split(a, av);
		append_node(a, (int)n);
		i++;
	}
}