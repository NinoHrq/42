/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:50:03 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:50:48 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norminette_one_kill(t_ee *ee, char **args)
{
	ft_printf("🍁_(`へ´*)_🍁: %s: command not found\n", args[0]);
	ee->signal = 127;
	if (ee->command_with_and == 1)
		ee->check_and_validity = 1;
	ee->command_with_or = 1;
	ee->confirmed_command = 0;
}

void	if_path_is_incorrect(char **args, t_ee *ee)
{
	if (args[0][0] != '$')
		norminette_one_kill(ee, args);
	else if (args[0][0] == '$' && args[0][1] <= 32)
		norminette_one_kill(ee, args);
	else if (args[0][0] == '$' && args[0][1] > 32)
	{
		if (ee->signal == 127 || ee->signal == 126)
			ee->confirmed_command = 0;
		else
			ee->confirmed_command = 1;
	}
	return ;
}

void	error_access(char *command)
{
	int	i;

	i = 0;
	if (command[i + 2] <= 32)
	{
		ft_printf("🚧_(⊙_⊙;)_🚧 : ./: Is a directory\n");
		exit(126);
	}
	if (access(command, X_OK) == -1)
	{
		ft_printf("%s: Permission denied\n", command);
		exit(126);
	}
}
