/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_little_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:28:26 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:28:28 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_unset(char *input, t_ee *ee)
{
	ft_unset(input, ee);
	ee->confirmed_command = 1;
	return ;
}

void	if_export(char *input, t_ee *ee)
{
	ft_export(input, ee);
	ee->confirmed_command = 1;
	return ;
}

void	if_dq(t_ee *ee, t_token *token)
{
	ft_printf("🍁_(`へ´*)_🍁: %d: command not found\n", ee->signal);
	ee->signal = 127;
	if (token->trimmed_input)
		free(token->trimmed_input);
	if (token)
		free(token);
	return ;
}

void	if_else(t_token *token, char *input, t_ee *ee)
{
	if (ee->minishell_check == 0)
		execute_external_command(input, ee);
	if (token->trimmed_input)
		free(token->trimmed_input);
	if (token)
		free(token);
	return ;
}
