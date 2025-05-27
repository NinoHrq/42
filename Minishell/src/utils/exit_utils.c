/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:32:38 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/07 20:11:17 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_simple_exit(char *input)
{
	int	i;

	i = 0;
	while (input[i] <= 32)
		i++;
	while (input[i] > 32)
		i++;
	return (0);
}

void	handle_exit_no_args(char **args, t_ee *ee, t_token *exit)
{
	ft_printf("🏃 exit\n");
	if (args)
		free_split(args);
	free(exit);
	ee->minishell_check = 1;
}

void	handle_exit_with_numeric_value(char **args, t_ee *ee, t_token *exit)
{
	ft_printf("🏃 exit\n");
	if (check_atoi_overflow(args[1]) == 1)
	{
		ft_printf("🚧_(⊙_⊙;)_🚧 : exit: %s: numeric argument required\n", args[1]);
		ee->code_exit = 2;
	}
	else
		ee->code_exit = ft_atoi(args[1]);
	free_split(args);
	free(exit);
	ee->minishell_check = 1;
}

void	handle_exit_with_status_value(char **args, t_ee *ee, t_token *exit)
{
	ft_printf("🏃 exit\n");
	ee->code_exit = ee->signal;
	free_split(args);
	free(exit);
	ee->minishell_check = 1;
}

void	handle_exit_too_many_args(t_token *exit, char **args, t_ee *ee)
{
	ft_printf("🏃 exit\n");
	ft_printf("💥_(╬ಠ益ಠ)_💥: exit: too many arguments\n");
	ee->signal = 2;
	ee->error_exit = 1;
	free_split(args);
	free(exit);
}
