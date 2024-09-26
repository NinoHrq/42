/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:08:25 by tmilin            #+#    #+#             */
/*   Updated: 2024/09/25 22:51:34 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sep && str[i] != '\0')
			i++;
		if (str[i] != sep && str[i] != '\0')
			count++;
		while (str[i] != sep && str[i] != '\0')
			i++;
	}
	return (count);
}

static void	ft_freetableau(char **tab, int len)
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

static void	tableau( char **tab, const char *str, char sep, int leng)
{
	int	i;
	int	j;
	int	k;
	int	m;

	i = 0;
	j = 0;
	while (str[i] != '\0' && j < leng)
	{
		while (str[i] != '\0' && str[i] == sep)
			i++;
		k = i;
		while (str[k] != '\0' && str[k] != sep)
			k++;
		tab[j] = malloc(sizeof(char) * (k - i + 1));
		if (!tab)
			return (ft_freetableau(tab, leng));
		m = 0;
		while (i < k)
		{
			tab[j][m++] = str[i++];
		}
		tab[j++][m] = '\0';
	}
	tab[j] = NULL;
}

char	**ft_split(const char *st, char sep)
{
	char	**dest;
	int		leng;

	if (!st)
		return (NULL);
	leng = count_words(st, sep);
	dest = malloc(sizeof(char *) * (leng + 1));
	if (!dest)
		return (NULL);
	tableau(dest, st, sep, leng);
	return (dest);
}
