/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:01:57 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 19:01:57 by tmilin           ###   ########.fr       */
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

void	ft_freetableautt(char **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	tableau_picasso(t_tableautt *tt)
{
	tt->i = 0;
	tt->j = 0;
	tt->in_quotes = 0;
}

static void	tableautt(char **tab, const char *str, char sep, int leng)
{
	t_tableautt	tt;

	tableau_picasso(&tt);
	while (str[tt.i] != '\0' && tt.j < leng)
	{
		while (str[tt.i] != '\0' && str[tt.i] == sep && !tt.in_quotes)
			tt.i++;
		if (str[tt.i] == '"')
		{
			tt.in_quotes = !tt.in_quotes;
			tt.i++;
		}
		tt.k = tt.i;
		while (str[tt.k] != '\0' && (str[tt.k] != sep || tt.in_quotes))
			tt.k++;
		tab[tt.j] = malloc(sizeof(char) * (tt.k - tt.i + 1));
		if (!tab)
			return (ft_freetableautt(tab, leng));
		tt.m = 0;
		while (tt.i < tt.k)
			tab[tt.j][tt.m++] = str[tt.i++];
		tab[tt.j++][tt.m] = '\0';
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

/*static void	tableautt(char **tab, const char *str, char sep, int leng)
{
	int	i;
	int	j;
	int	k;
	int	m;
	int	in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	while (str[i] != '\0' && j < leng)
	{
		while (str[i] != '\0' && str[i] == sep && !in_quotes)
			i++;
		if (str[i] == '"')
		{
			in_quotes = !in_quotes;
			i++;
		}
		k = i;
		while (str[k] != '\0' && (str[k] != sep || in_quotes))
			k++;
		tab[j] = malloc(sizeof(char) * (k - i + 1));
		if (!tab)
			return (ft_freetableautt(tab, leng));
		m = 0;
		while (i < k)
			tab[j][m++] = str[i++];
		tab[j++][m] = '\0';
	}
	tab[j] = NULL;
}*/
