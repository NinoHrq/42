/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:30:56 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/04 17:02:41 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_separators(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if ((input[i] > 32 && (input[i + 1] == '<' || input[i + 1] == '>'))
			|| ((input[i] == '<' || input[i] == '>') && input[i + 1] > 32))
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	*allocate_good_sep(char *input, int extra_spaces)
{
	char	*good_sep;

	good_sep = malloc(sizeof(char) * (ft_strlen(input) + extra_spaces + 2));
	if (!good_sep)
		return (NULL);
	return (good_sep);
}

void	what_a_lovely_day_yippe_ki_yay_motherfucker(t_separator_handler *sh,
		char *input)
{
	sh->quote = input[sh->i];
	sh->quote = input[sh->i++];
	while (input[sh->i] && input[sh->i] != sh->quote)
		sh->i++;
	if (input[sh->i] == sh->quote)
		sh->i++;
}

void	fill_good_sep(t_separator_handler *sh, char *input)
{
	while (input[sh->i])
	{
		if (input[sh->i] == '"' || input[sh->i] == '\'')
			what_a_lovely_day_yippe_ki_yay_motherfucker(sh, input);
		else if (sh->i > 0 && input[sh->i - 1] > 32 && (input[sh->i] == '<'
				|| input[sh->i] == '>'))
			sh->good_sep[sh->j++] = ' ';
		if ((input[sh->i] == '<' && input[sh->i + 1] == '<')
			|| (input[sh->i] == '>' && input[sh->i + 1] == '>'))
		{
			sh->good_sep[sh->j++] = input[sh->i++];
			sh->good_sep[sh->j++] = input[sh->i];
			sh->good_sep[sh->j++] = ' ';
		}
		else if (input[sh->i] == '<' || input[sh->i] == '>')
		{
			sh->good_sep[sh->j++] = input[sh->i];
			sh->good_sep[sh->j++] = ' ';
		}
		else
			sh->good_sep[sh->j++] = input[sh->i];
		sh->i++;
	}
	sh->good_sep[sh->j] = '\0';
}

/*void	fill_good_sep(t_separator_handler *sh, char *input)
{
	t_separator_handler	sh;

	while (input[sh->i])
	{
		if (sh->i > 0 && input[sh->i - 1] > 32 && (input[sh->i] == '<'
				|| input[sh->i] == '>'))
			sh->good_sep[sh->j++] = ' ';
		if ((input[sh->i] == '<' && input[sh->i + 1] == '<')
			|| (input[sh->i] == '>' && input[sh->i + 1] == '>'))
		{
			sh->good_sep[sh->j++] = input[sh->i++];
			sh->good_sep[sh->j++] = input[sh->i];
			sh->good_sep[sh->j++] = ' ';
		}
		else if (input[sh->i] == '<' || input[sh->i] == '>')
		{
			sh->good_sep[sh->j++] = input[sh->i];
			sh->good_sep[sh->j++] = ' ';
		}
		else
			sh->good_sep[sh->j++] = input[sh->i];
		sh->i++;
	}
	sh->good_sep[sh->j] = '\0';
}*/
char	*unstick_to_re_stick(char *input)
{
	t_separator_handler	sh;

	sh.i = 0;
	sh.j = 0;
	sh.quote = '\0';
	sh.count_how_many_sep = count_separators(input);
	sh.good_sep = allocate_good_sep(input, sh.count_how_many_sep);
	if (!sh.good_sep)
		return (NULL);
	fill_good_sep(&sh, input);
	return (sh.good_sep);
}

/*char	*unstick_to_re_stick(char *input)
{
	int		i, j;
	int		count_how_many_sep;
	char	*good_sep;

	i = 0, j = 0;
	count_how_many_sep = 0;
	while (input[i])
	{
		if ((input[i] > 32 && (input[i + 1] == '<' || input[i + 1] == '>'))
			|| ((input[i] == '<' || input[i] == '>') && input[i + 1] > 32))
		{
			count_how_many_sep++;
		}
		i++;
	}
	good_sep = malloc(sizeof(char) * (i + count_how_many_sep + 2));
	if (!good_sep)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (i > 0 && input[i - 1] > 32 && (input[i] == '<' || input[i] == '>'))
			good_sep[j++] = ' ';
		if (input[i] == '<' && input[i + 1] == '<')
		{
			good_sep[j++] = input[i++];
			good_sep[j++] = input[i];
			good_sep[j++] = ' ';
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			good_sep[j++] = input[i++];
			good_sep[j++] = input[i];
			good_sep[j++] = ' ';
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			good_sep[j++] = input[i];
			good_sep[j++] = ' ';
		}
		else
			good_sep[j++] = input[i];
		i++;
	}
	good_sep[j] = '\0';
	return (good_sep);
}*/
