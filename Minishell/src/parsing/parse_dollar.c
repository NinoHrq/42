/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:30:20 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/04 21:08:11 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_var_name(char *arg)
{
	char	*copy;
	int		j;
	int		k;

	j = 1;
	k = 0;
	copy = malloc(sizeof(char) * ft_strlen(arg));
	if (!copy)
		return (NULL);
	while (arg[j])
		copy[k++] = arg[j++];
	copy[k] = '\0';
	return (copy);
}

char	*get_env_value(char *var_name, t_ee *ee)
{
	int	x;
	int	len;

	x = 0;
	var_name = parse_env_value(var_name);
	len = ft_strlen(var_name);
	while (ee->envp[x])
	{
		if (ft_strncmp(ee->envp[x], var_name, len) == 0
			&& ee->envp[x][len] == '=')
		{
			free(var_name);
			return (ft_strdup(ee->envp[x] + len + 1));
		}
		x++;
	}
	free(var_name);
	return (NULL);
}

char	*handle_dollar_variable(char *arg, t_ee *ee)
{
	char	*copy;
	char	*value;
	char	*result;

	copy = extract_var_name(arg);
	if (!copy)
		return (NULL);
	value = get_env_value(copy, ee);
	free(copy);
	if (value)
		result = value;
	else
		result = ft_strdup(arg);
	return (result);
}

char	*extract_text_before_dollar(char *arg)
{
	int		j;
	char	*before_equal;

	j = 0;
	while (arg[j] && arg[j] != '$')
		j++;
	before_equal = malloc(sizeof(char) * (j + 1));
	if (!before_equal)
		return (NULL);
	ft_strncpy(before_equal, arg, j);
	before_equal[j] = '\0';
	return (before_equal);
}

char	**parse_dollars(char **args, t_ee *ee)
{
	t_dollar_parser	p;

	p.changed_args = malloc(sizeof(char *) * (ft_strlonglen(args) + 1));
	p.i = 0;
	while (args[p.i])
	{
		p.lock = 0;
		if (args[p.i][0] == '$')
			p.changed_args[p.i] = handle_dollar_variable(args[p.i], ee);
		else
		{
			p.before_equal = extract_text_before_dollar(args[p.i]);
			if (p.before_equal)
			{
				p.changed_args[p.i] = p.before_equal;
				p.lock = 1;
			}
			if (!p.lock)
				p.changed_args[p.i] = ft_strdup(args[p.i]);
		}
		p.i++;
	}
	p.changed_args[p.i] = NULL;
	return (p.changed_args);
}
