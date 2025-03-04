/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:31:23 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:31:24 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norminette_tricks(void)
{
	ft_printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `newline'\n");
}

int	check_the_end(char *input)
{
	(void)input;
	return (0);
}

int	do_you_find_or_what(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '(')
		{
			while (input[i] != ')')
				i++;
		}
		if (input[i] == '|' && input[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	find_parenthesis(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ')')
			return (1);
		i++;
	}
	return (0);
}

/*char	**parse_dollars(char **args, t_ee *ee)
{
	char	*copy;
	char	**changed_args;
	char	*after_equal;
	char	*before_equal;
	int		lock;

	int i, j, k, x, y, m;
	changed_args = malloc(sizeof(char *) * (ft_strlonglen(args) + 1));
	if (!changed_args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		lock = 0;
		if (args[i][0] == '$')
		{
			copy = malloc(sizeof(char) * ft_strlen(args[i]));
			if (!copy)
				return (NULL);
			j = 1;
			k = 0;
			while (args[i][j])
				copy[k++] = args[i][j++];
			copy[k] = '\0';
			x = 0;
			while (ee->envp[x])
			{
				y = 0;
				if (ft_strncmp(ee->envp[x], copy, ft_strlen(copy)) == 0
					&& ee->envp[x][ft_strlen(copy)] == '=')
				{
					y = ft_strlen(copy) + 1;
					after_equal = ft_strdup(ee->envp[x] + y);
					if (!after_equal)
						return (NULL);
					changed_args[i] = after_equal;
					lock = 1;
					break ;
				}
				x++;
			}
			if (!lock)
				changed_args[i] = ft_strdup(args[i]);
			free(copy);
		}
		else
		{
			j = 0;
			while (args[i][j] && args[i][j] != '$')
				j++;
			if (args[i][j] == '$')
			{
				m = j;
				before_equal = malloc(sizeof(char) * (m + 1));
				if (!before_equal)
					return (NULL);
				k = 0;
				while (k < m)
				{
					before_equal[k] = args[i][k];
					k++;
				}
				before_equal[m] = '\0';
				changed_args[i] = before_equal;
				lock = 1;
			}
			if (!lock)
				changed_args[i] = ft_strdup(args[i]);
		}
		i++;
	}
	changed_args[i] = NULL;
	return (changed_args);
}*/
