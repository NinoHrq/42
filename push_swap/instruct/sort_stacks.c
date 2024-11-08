/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:46:10 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/08 22:51:13 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	move_a_to_b(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*cheapest_node;

	cheapest_node = get_cheapest(*a);
	if (cheapest_node->median && cheapest_node->target->median)
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->median)
		&& !(cheapest_node->target->median))
		reverse_rotate_both(a, b, cheapest_node);
	befor_push(a, cheapest_node, 'a');
	befor_push(b, cheapest_node->target, 'b');
    pb(b, a);
}

static void	move_b_to_a(t_stack_node **a, t_stack_node **b)
{
	befor_push(a, (*b)->target, 'a');
	pa(a, b);
}

static void	min_on_top(t_stack_node **a)
{
	while ((*a)->nb != find_min(*a)->nb)
	{
		if (find_min(*a)->median)
			ra(a);
		else
			rra(a);
	}
}

void	sort_stacks(t_stack_node **a, t_stack_node **b)
{
	int	len_a;

	len_a = stack_len(*a);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a);
	while (len_a-- > 3 && !stack_sorted(*a))
	{
		init_nodes_a(*a, *b);
		move_a_to_b(a, b);
	}
	sort_3(a);
	while (*b)
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
	current_index(*a);
	min_on_top(a);
}