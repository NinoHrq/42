/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:31:34 by nharraqi          #+#    #+#             */
/*   Updated: 2024/09/14 17:09:36 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab);

static int count_words(const char *str, char sep)
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

static char	**tableau(const char *str, char sep, int leng)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int		m;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (leng + 1));
	if (!tab)
		return (NULL);
	while (str[i] != '\0' && j < leng)
	{
		while (str[i] != '\0' && str[i] == sep)
			i++;
		k = i;
		while (str[k] != '\0' && str[k] != sep)
			k++;
		tab[j] = malloc(sizeof(char) * (k - i + 1));
		if (!tab[j])
		{
			free_tab(tab); // Libère toute la mémoire déjà allouée
			return (NULL);
		}
		m = 0;
		while (i < k)
			tab[j][m++] = str[i++];
		tab[j][m] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab); // Ne pas libérer ici
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_split(const char *s, char c)
{
	char	**dest;
	int		leng;

	if (!s)
		return (NULL);
	leng = count_words(s, c);
	dest = tableau(s, c, leng);
	return (dest);
}
