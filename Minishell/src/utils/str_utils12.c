/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils12.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:20:09 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/08 11:54:14 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	found_single_pipe__(char *input)
{
	int		i;
	char	quote_type;
	int		found_redir;

	i = 0;
	quote_type = 0;
	found_redir = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote_type == 0)
				quote_type = input[i];
			else if (quote_type == input[i])
				quote_type = 0;
		}
		if (quote_type == 0 && (input[i] != '|' && input[i + 1] == '|'))
		{
			found_redir = 1;
		}
		i++;
	}
	return (found_redir);
}

void	the_really_last_function(char *input, int *i)
{
	(*i)++;
	while (input[*i] && (input[*i] != '"' || input[*i] != '\''))
		(*i)++;
	if ((input[*i] == '"' || input[*i] == '\'') && input[*i + 1])
		(*i)++;
}
