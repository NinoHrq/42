/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:01:59 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/07 18:54:05 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_extra_spaces_pipeline(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (i > 0 && input[i - 1] > 32)
				count++;
			if (input[i + 1] && input[i + 1] > 32)
				count++;
		}
		i++;
	}
	return (count);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	remoov_single__quote__(char **args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "'$?'") == 0 && args[i + 1])
			i++;
		else if (ft_strcmp(args[i], "'$?'") == 0)
			break ;
		j = 0;
		k = 0;
		while (args[i][j])
		{
			if (args[i][j] != '\'')
				args[i][k++] = args[i][j];
			j++;
		}
		args[i][k] = '\0';
		i++;
	}
}

int	f_sq(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
