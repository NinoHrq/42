/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:25:36 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:25:37 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	confirme_n(char *input)
{
	int	i;

	i = 0;
	if (input[i] != '-')
		return (0);
	i = 1;
	while (input[i] && input[i] == 'n')
	{
		if (input[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

bool	is_single_quoted(const char *str)
{
	return (str[0] == '\'' && str[strlen(str) - 1] == '\'');
}

char	**parse_dollarsss(char **args, t_ee *ee)
{
	int		i;
	char	**changed_args;

	i = 0;
	changed_args = malloc(sizeof(char *) * (sizeof(args) + 1));
	if (!changed_args)
		return (NULL);
	while (args[i])
	{
		if (ft_strcmp(args[i], "$?") == 0)
		{
			do_what_dq_do(ee);
			break ;
		}
		else if (is_single_quoted(args[i]) && ft_strcmp(args[i], "$?"))
			changed_args[i] = strdup(args[i]);
		else if (args[i][0] == '$' && ft_strcmp(args[i], "$?"))
			changed_args[i] = get_env_value(args[i] + 1, ee);
		else
			changed_args[i] = strdup(args[i]);
		i++;
	}
	changed_args[i] = NULL;
	return (changed_args);
}

void	printf_echo(char **args, t_ee *ee)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "$?") == 0)
			ft_printf("%d", ee->signal);
		else
		{
			if (confirme_n(args[i]) != 1)
				ft_printf("%s", args[i]);
			if (confirme_n(args[i]) == 1 && i > 1)
				ft_printf("%s", args[i]);
		}
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
}

void	ft_echo(char *input, t_ee *ee)
{
	char	**args;
	char	**tmp;
	bool	no_newline;

	no_newline = false;
	args = ft_splittt(input, ' ');
	remoov_quote__(args);
	tmp = parse_dollarsss(args, ee);
	free_split(args);
	args = tmp;
	if (args[1] && confirme_n(args[1]) == 1)
		no_newline = true;
	printf_echo(args, ee);
	if (!no_newline)
		ft_printf("\n");
	free_split(args);
}
