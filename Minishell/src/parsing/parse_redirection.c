/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:01:56 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:30:48 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_extra_spaces(char *l)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (l[i])
	{
		if (l[i] > 32 && l[i] != '<' && l[i] != '>' && (l[i + 1] == '<' || l[i
					+ 1] == '>'))
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	*parse_redirection_at_start(char *l)
{
	int		i;
	int		j;
	int		extra_spaces;
	char	*tmp;

	i = 0;
	j = 0;
	extra_spaces = count_extra_spaces(l);
	tmp = malloc(sizeof(char) * (strlen(l) + extra_spaces + 1));
	if (!tmp)
		return (NULL);
	while (l[i])
	{
		if (l[i] > 32 && l[i] != '<' && l[i] != '>' && (l[i + 1] == '<' || l[i
					+ 1] == '>'))
		{
			tmp[j++] = l[i];
			tmp[j++] = ' ';
		}
		else
			tmp[j++] = l[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*cut_for_no_leaks_at_the_end(char *input)
{
	char	*tmp;

	tmp = parse_redirection_at_start(input);
	return (tmp);
}

int	count_first_or_last(char *input, char c)
{
	int	i;
	int	count_first;
	int	count_last;

	count_first = 0;
	count_last = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '(')
			count_first++;
		if (input[i] == ')')
			count_last++;
		i++;
	}
	if (c == 'f')
		return (count_first);
	else
		return (count_last);
	return (0);
}
