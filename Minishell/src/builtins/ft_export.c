/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:26:26 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:26:27 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(char *input, t_ee *ee)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!ee->envp || !ee->envp[0])
	{
		bilbon_saquet(ee, args);
		free_split(args);
		return ;
	}
	if (ft_strcmp(args[0], "export=") == 0)
	{
		free_split(args);
		return ;
	}
	if (!args[1])
		process_simple_export(input, ee);
	else
		norminette_backstab(ee, args);
	free_split(args);
}

/*void	ft_export(char *input, t_ee *ee)
{
	char **args;
	char **sorted_env;
	char **concatene_both_tab = NULL;

	args = ft_split(input, ' ');
	if (!ee->envp || !ee->envp[0])
	{
		bilbon_saquet(ee, args);
		return ;
	}
	if (ft_strcmp(args[0], "export=") == 0)
	{
		free_split(args);
		return ;
	}
	if (!args[1])
	{
		input = parse_input_simple_export(input);
		if (ft_strcmp(input, "export") == 0)
			concatene_both_tab = copi_colle(ee);
		sorted_env = remove_duplicates_with_priority(concatene_both_tab);
		sort_export(ee, sorted_env);
		free_split(sorted_env);
		free_split(concatene_both_tab);
		free(input);
	}
	else
		norminette_backstab(ee, args);
	free_split(args);
}*/
