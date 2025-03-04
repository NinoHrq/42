/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:30:27 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:30:28 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*parse_input_simple_export(char *input)
{
	int		i;
	int		j;
	char	*copy;
	int		start;

	i = 0;
	j = 0;
	while (input[i] && input[i] <= 32)
		i++;
	start = i;
	while (input[i] && input[i] > 32)
		i++;
	copy = malloc(sizeof(char) * (i - start + 1));
	if (!copy)
		return (NULL);
	while (start < i)
	{
		copy[j] = input[start];
		start++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

int	ft_found_equal(char c)
{
	if (c == '=')
		return (1);
	return (0);
}

int	ft_check_equal(const char *s)
{
	return (ft_strchr(s, '=') != NULL);
}
