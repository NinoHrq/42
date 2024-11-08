/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pushswap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:09:38 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/08 23:09:41 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

static int	ft_isspace(char c)
{
	return (c <= 32);
}

static int	ft_count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]))
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

void	ft_putstrs(char **strs, char *str, int words)
{
	int	i;
	int	j;
	int	start;
	int	end;

	j = 0;
	start = 0;
	while (str[start] && j < words)
	{
		i = 0;
		while (str[start] && ft_isspace(str[start]))
			start++;
		end = start;
		while (str[end] && !ft_isspace(str[end]))
			end++;
		strs[j] = malloc(sizeof(char) * (end - start + 1));
		if (!strs[j])
			return (free_av(strs));
		while (start < end)
			strs[j][i++] = str[start++];
		strs[j++][i] = '\0';
	}
	strs[j] = 0;
}

char	**split_for_push_swap(char *str)
{
	int		words;
	char	**strs;

	words = ft_count_words(str);
	if (!words)
		return (NULL);
	strs = malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	ft_putstrs(strs, str, words);
	return (strs);
}