/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_little_one.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:28:18 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:28:19 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_echo(char *input, t_ee *ee)
{
	ft_echo(input, ee);
	ee->confirmed_command = 1;
	return ;
}

void	if_exit(t_token *token, char *input, t_ee *ee)
{
	if (ft_strcmp(token->trimmed_input, "exit") == 0
		&& ft_strcmp(token->trimmed_input, input) == 0)
	{
		ft_printf("🏃 exit\n");
		ee->minishell_check = 1;
	}
	else
		ft_exit(input, ee);
}

void	if_pwd(t_ee *ee)
{
	ft_pwd();
	ee->confirmed_command = 1;
	return ;
}

void	if_cd(char *input, t_ee *ee)
{
	if (ee->copy_oldpwd)
		free(ee->copy_oldpwd);
	ft_cd(input, ee);
	ee->confirmed_command = 1;
}

void	if_env(t_ee *ee)
{
	if (ee->path_is_not_able == 0 && ee->lock_path == 0)
	{
		ft_env(ee);
		ee->confirmed_command = 1;
	}
	else
	{
		ft_printf("🌳(´•︵•`)🌳: env: No such file or directory\n");
		ee->confirmed_command = 0;
	}
	return ;
}
