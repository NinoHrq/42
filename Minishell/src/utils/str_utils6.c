/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:54:03 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 16:54:03 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remoov_quote__(char **args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (args[i])
	{
		j = 0;
		k = 0;
		while (args[i][j])
		{
			if (args[i][j] != '"')
				args[i][k++] = args[i][j];
			j++;
		}
		args[i][k] = '\0';
		i++;
	}
}

int	found_single_or_double_quote(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '(')
			return (0);
		if (input[i] == '\'' || input[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	found_single_or_double__(char *input)
{
	int		i;
	char	quote_type;
	int		found_operator;

	i = 0;
	quote_type = 0;
	found_operator = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote_type == 0)
				quote_type = input[i];
			else if (quote_type == input[i])
				quote_type = 0;
		}
		if (quote_type == 0)
		{
			if ((input[i] == '|' && input[i + 1] == '|'))
				found_operator = 1;
		}
		i++;
	}
	return (found_operator);
}

int	found_single__(char *input)
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
		if (quote_type == 0)
		{
			if ((input[i] == '<' || input[i + 1] == '>'))
				found_redir = 1;
		}
		i++;
	}
	return (found_redir);
}
