/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:01:57 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/07 21:03:35 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_wordstt(const char *str, char sep)
{
	int	i;
	int	count;
	int	in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			in_quotes = !in_quotes;
		while (!in_quotes && str[i] == sep && str[i] != '\0')
			i++;
		if (!in_quotes && str[i] != sep && str[i] != '\0')
			count++;
		while (!in_quotes && str[i] != sep && str[i] != '\0')
			i++;
		if (in_quotes)
			i++;
	}
	return (count);
}

void	find_token_end(const char *str, char sep, t_tableautt *tt)
{
	tt->k = tt->i;
	tt->in_quotes = 0;
	while (str[tt->k])
	{
		if (str[tt->k] == '"' || str[tt->k] == '\'')
			tt->in_quotes = !tt->in_quotes;
		else if (str[tt->k] == sep && !tt->in_quotes)
			break ;
		tt->k++;
	}
}

int	allocate_and_copy(char **tab, const char *str, t_tableautt *tt)
{
	tab[tt->j] = malloc(sizeof(char) * (tt->k - tt->i + 1));
	if (!tab[tt->j])
		return (0);
	tt->m = 0;
	while (tt->i < tt->k)
	{
		tab[tt->j][tt->m++] = str[tt->i];
		tt->i++;
	}
	tab[tt->j][tt->m] = '\0';
	return (1);
}

static void	tableautt(char **tab, const char *str, char sep, int leng)
{
	t_tableautt	tt;

	tableau_picasso(&tt);
	while (str[tt.i] && tt.j < leng)
	{
		skip_separators(str, sep, &tt);
		find_token_end(str, sep, &tt);
		if (!allocate_and_copy(tab, str, &tt))
			return ;
		tt.j++;
		if (str[tt.i] == sep)
			tt.i++;
	}
	tab[tt.j] = NULL;
}

char	**ft_splittt(const char *st, char sep)
{
	char	**dest;
	int		leng;

	if (!st)
		return (NULL);
	leng = count_wordstt(st, sep);
	dest = malloc(sizeof(char *) * (leng + 1));
	if (!dest)
		return (NULL);
	tableautt(dest, st, sep, leng);
	return (dest);
}
