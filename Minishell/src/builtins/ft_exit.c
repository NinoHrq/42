/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:26:09 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:26:10 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char *input, t_ee *ee)
{
	t_token	*exit;
	char	**args;

	exit = malloc(sizeof(t_token));
	exit->token = 0;
	input = parse_input_exit(input, exit);
	args = ft_split(input, ' ');
	if (check_simple_exit(input) == 0 && args[1] == NULL)
	{
		handle_exit_no_args(args, ee, exit);
		return ;
	}
	if (exit->token == 1)
	{
		handle_exit_syntax_error();
		return ;
	}
	process_exit(args, ee, exit);
}

void	process_exit(char **args, t_ee *ee, t_token *exit)
{
	if ((args[1] && (ft_strcmp(args[1], "$?") == 0) && args[1][0] != ';'))
		handle_exit_with_status_value(args, ee, exit);
	else if (args[1] && !is_number(args[1]) && args[1][0] != ';')
		handle_exit_numeric_error(args, ee, exit);
	else if (args[2] != NULL && args[1][0] != ';' && args[2][0] != ';')
		handle_exit_too_many_args(exit, args, ee);
	else if ((args[1] && is_number(args[1]) && args[1][0] != ';'))
		handle_exit_with_numeric_value(args, ee, exit);
	else
		handle_exit_no_args(args, ee, exit);
}

/*void	ft_exit(char *input, t_ee *ee)
{
	t_token	*exit;
	char	**args;

	exit = malloc(sizeof(t_token));
	exit->token = 0;
	input = parse_input_exit(input, exit);
	args = ft_split(input, ' ');
	if (check_simple_exit(input) == 0 && args[1] == NULL)
	{
		ft_printf("🏃 exit\n");
		if (args)
			free_split(args);
		free(exit);
		ee->minishell_check = 1;
		return ;
	}
	if (exit->token == 1)
	{
		printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;'\n");
		return ;
	}
	if (args[1] && !is_number(args[1]) && args[1][0] != ';')
	{
		ft_printf("exit\n");
		ft_printf("🚧_(⊙_⊙;)_🚧 : exit: %s: numeric argument required\n",
			args[1]);
		free_split(args);
		free(exit);
		ee->minishell_check = 1;
	}
	else if (args[2] != NULL && args[1][0] != ';' && args[2][0] != ';')
	{
		ft_printf("exit\n");
		ft_printf("💥_(╬ಠ益ಠ)_💥: exit: too many arguments\n");
	}
	else
	{
		ft_printf("🏃 exit\n");
		free_split(args);
		free(exit);
		ee->minishell_check = 1;
	}
}*/
