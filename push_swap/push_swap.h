/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:33:31 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/08 23:00:01 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "libft.h"
#include <stdbool.h>  
#include <limits.h>

typedef struct s_stack_node
{
	int					nb;
	int					index;
	int					push_cost;
	bool				median;
	bool				cheapest;
	struct s_stack_node	*target;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}						t_stack_node;

void					init_node_value(t_stack_node *node, int n);
void					free_errors_for_split(t_stack_node **a, char **av);
void					init_stack_a_for_split(t_stack_node **a, char **av);
void					free_av(char **av);
int						ft_atol(char *str, t_stack_node **stack);
void					check_atol(long number, int sign, t_stack_node **stack);
int						ft_atol_for_split(char *str, t_stack_node **stack,
							char **av);
void					check_atol_split(long n, int sign, t_stack_node **s,
							char **av);
int						check_double(t_stack_node *a, int n);
void					free_stack(t_stack_node **stack);
void					free_errors(t_stack_node **a);
void					init_stack_a(t_stack_node **a, char **argv);
void					init_nodes_a(t_stack_node *a, t_stack_node *b);
void					init_nodes_b(t_stack_node *a, t_stack_node *b);
void					current_index(t_stack_node *stack);
void					set_cheapest(t_stack_node *stack);
t_stack_node			*get_cheapest(t_stack_node *stack);
void					befor_push(t_stack_node **s, t_stack_node *n,
							char c);
int						stack_len(t_stack_node *stack);
t_stack_node			*find_last(t_stack_node *stack);
bool					stack_sorted(t_stack_node *stack);
t_stack_node			*find_min(t_stack_node *stack);
t_stack_node			*find_max(t_stack_node *stack);
void					sa(t_stack_node **a);
void					sb(t_stack_node **b);
void					ss(t_stack_node **a, t_stack_node **b);
void					ra(t_stack_node **a);
void					rb(t_stack_node **b);
void					rr(t_stack_node **a, t_stack_node **b);
void					rra(t_stack_node **a);
void					rrb(t_stack_node **b);
void					rrr(t_stack_node **a, t_stack_node **b);
void					pa(t_stack_node **a, t_stack_node **b);
void					pb(t_stack_node **b, t_stack_node **a);
void					rotate_both(t_stack_node **a, t_stack_node **b,
							t_stack_node *cheapest_node);
void					reverse_rotate_both(t_stack_node **a, t_stack_node **b,
							t_stack_node *cheapest_node);
void					sort_3(t_stack_node **a);
void					sort_stacks(t_stack_node **a, t_stack_node **b);
char					**split_for_push_swap(char *str);

#endif