/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:35:03 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:35:04 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	at_the_end(t_token *token, t_ee *ee)
{
	if (token->trimmed_input)
		free(token->trimmed_input);
	if (token)
		free(token);
	if (ee->error_exit != 1)
		ee->signal = 0;
	ee->error_exit = 0;
}

void	all_is__freed(t_ee *ee)
{
	int	i;

	i = 0;
	while (ee->envp[i])
	{
		free(ee->envp[i]);
		i++;
	}
	if (ee->copy_oldpwd)
		free(ee->copy_oldpwd);
	if (ee->copy_pwd)
		free(ee->copy_pwd);
	if (ee->envp)
		free(ee->envp);
	if (ee->copy_export_env)
		free_split(ee->copy_export_env);
	if (ee->save_initial_path)
		free(ee->save_initial_path);
	if (ee->copy_home)
		free(ee->copy_home);
	free(ee);
}

void	free_after_or(char *command_before_or, char *command_after_or, t_ee *ee)
{
	if (command_before_or)
		free(command_before_or);
	if (command_after_or)
		free(command_after_or);
	ee->command_with_or = 0;
	return ;
}
