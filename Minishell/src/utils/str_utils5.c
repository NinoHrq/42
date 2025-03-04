/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:38:35 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:48:28 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (!to_find)
		return (str);
	while (str[i])
	{
		j = 0;
		while (to_find && to_find[i] && str[i + j])
		{
			if (to_find[j] == '\0')
				return (str + i);
			j++;
		}
		i++;
	}
	return (str);
}

int	check_atoi_overflow(char *str)
{
	long long int	result;
	int				sign;
	int				digit;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > (LLONG_MAX - digit) / 10)
			return (1);
		result = result * 10 + digit;
		str++;
	}
	return (0);
}

void	copy_until_close_quote(char *l, int *i, char *copy, int *j)
{
	char	quote_type;

	quote_type = l[*i];
	copy[(*j)++] = l[(*i)++];
	while (l[*i] != '\0')
	{
		copy[(*j)++] = l[*i];
		if (l[*i] == quote_type)
		{
			(*i)++;
			return ;
		}
		(*i)++;
	}
}

void	copy_until_parenthesis(char *l, int *i, char *copy, int *j)
{
	while (l[*i] != '\0' && (*i == 0 || l[*i - 1] != ')'))
	{
		copy[*j] = l[*i];
		(*j)++;
		(*i)++;
	}
	if (l[*i] == ')')
		(*i)++;
}

size_t	ft_strcspn(const char *str, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (reject[j] != '\0')
		{
			if (str[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
