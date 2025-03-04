/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:37:25 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:37:55 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	has_no_or(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	find_redirection_and_pipe(char *input)
{
	int	i;
	int	found_re;

	i = 0;
	found_re = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			found_re++;
			break ;
		}
		i++;
	}
	if (found_re != 0 && has_no_or(input) == 0)
	{
		while (input[i])
		{
			if (input[i] == '|' && input[i + 1] != '|' && input[i - 1] != '|')
				return (1);
			i++;
		}
	}
	return (0);
}

int	find_redirection(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	find_type_of_redirection(char *tmp_in)
{
	int	i;

	i = 0;
	while (tmp_in && tmp_in[i])
	{
		if (tmp_in[i] == '>' && tmp_in[i + 1] != '>')
			return (3);
		else if (tmp_in[i] == '>' && tmp_in[i + 1] == '>')
			return (2);
		else if (tmp_in[i] == '<' && tmp_in[i + 1] != '<')
			return (1);
		else if (tmp_in[i] == '<' && tmp_in[i + 1] == '<')
			return (4);
		i++;
	}
	return (0);
}

char	*foud_delimiter(char **split_in)
{
	char	*tmp;
	int		i;

	i = 0;
	while (split_in[i])
	{
		if (ft_strcmp(split_in[i], "<") == 0)
			break ;
		i++;
	}
	i++;
	i++;
	tmp = ft_strdup(split_in[i]);
	return (tmp);
}
