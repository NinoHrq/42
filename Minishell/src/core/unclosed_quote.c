/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:29:56 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:29:57 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	count_quotes(const char *input, t_quote *qt)
{
	int	i;

	i = 0;
	qt->single_quotes = 0;
	qt->double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			(qt->single_quotes)++;
		else if (input[i] == '"')
			(qt->double_quotes)++;
		i++;
	}
}

char	*append_next_line(char *input, t_ee *ee)
{
	char	*next_line;
	char	*new_input;

	next_line = readline("> ");
	if (!next_line)
	{
		free(input);
		ee->minishell_check = 1;
		return (NULL);
	}
	new_input = malloc(ft_strlen(input) + ft_strlen(next_line) + 2);
	if (!new_input)
	{
		free(input);
		free(next_line);
		return (NULL);
	}
	strcpy(new_input, input);
	strcat(new_input, next_line);
	strcat(new_input, "\n");
	free(input);
	free(next_line);
	return (new_input);
}

char	*handle_unclosed_quotes(char *input, t_ee *ee)
{
	t_quote	qt;

	init_quote_struct(&qt);
	while (input && *input)
	{
		count_quotes(input, &qt);
		if (qt.single_quotes % 2 != 0 || qt.double_quotes % 2 != 0)
		{
			input = append_next_line(input, ee);
			if (!input)
				return (NULL);
		}
		else
			break ;
	}
	return (input);
}
