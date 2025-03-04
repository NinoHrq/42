/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:28:07 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:28:08 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	command_part_one(t_token *token, char *input, t_ee *ee)
{
	int	res;

	res = 0;
	if (ft_strcmp(token->trimmed_input, "echo") == 0)
	{
		if_echo(input, ee);
		res = 1;
	}
	else if (ft_strcmp(token->trimmed_input, "exit") == 0)
	{
		if_exit(token, input, ee);
		res = 1;
	}
	else if (ft_strcmp(token->trimmed_input, "pwd") == 0)
	{
		if_pwd(ee);
		res = 1;
	}
	else if ((ft_strcmp(token->trimmed_input, "cd") == 0)
		|| (ft_strcmp(token->trimmed_input, "~") == 0))
	{
		if_cd(input, ee);
		res = 1;
	}
	return (res);
}

int	command_part_two(t_token *token, char *input, t_ee *ee)
{
	int	res;

	res = 0;
	if (ft_strcmp(token->trimmed_input, "env") == 0)
	{
		if_env(ee);
		res = 1;
	}
	else if (ft_strcmp(token->trimmed_input, "unset") == 0)
	{
		if_unset(input, ee);
		res = 1;
	}
	else if ((ft_strcmp(token->trimmed_input, "export") == 0)
		|| (ft_strcmp(token->trimmed_input, "export=") == 0))
	{
		if_export(input, ee);
		res = 1;
	}
	return (res);
}

int	interprete_commande(char *input, t_ee *ee)
{
	t_token	*token;

	if (handle_or_and_redirection(input, ee) == 1)
		return (0);
	token = malloc(sizeof(t_token));
	init_value_token(token, input);
	if (command_part_one(token, input, ee) == 0)
	{
		if (command_part_two(token, input, ee) == 0)
		{
			if (ft_strcmp(token->trimmed_input, "$?") == 0)
			{
				if_dq(ee, token);
				return (0);
			}
			else
			{
				if_else(token, input, ee);
				return (0);
			}
		}
	}
	at_the_end(token, ee);
	return (0);
}
