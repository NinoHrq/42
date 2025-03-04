/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:38:56 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:38:57 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_token(char *input, t_token *token)
{
	int	i;

	i = 0;
	while (input[i] <= 32)
		i++;
	if (input[i] == ';' && input[i + 1] != ';')
	{
		token->token = 1;
		return (1);
	}
	return (0);
}

int	check_after_token(char *input, int i)
{
	int	confirme;

	confirme = 0;
	if (input[i] && input[i + 1])
		i++;
	while (input[i] && input[i] <= 32)
	{
		if (input[i] > 32)
		{
			confirme = 1;
			break ;
		}
		i++;
	}
	if (confirme == 1)
		return (0);
	else
		return (1);
}

int	check_for_no_double(char *input, t_ee *ee)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '|' && input[i + 1] == '|') || (input[i] == '&'
				&& input[i + 1] == '&'))
		{
			i += 2;
			while (input[i] && input[i] <= 32)
				i++;
			if (input[i] == '|' || input[i] == '&' || input[i] == ';')
			{
				printf("🛠️_(>_<;)_🛠️   : syntax error\n");
				ee->signal = 2;
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}
