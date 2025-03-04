/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:34 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:34:35 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	bilbon_saquet(t_ee *ee, char **args)
{
	if (!ee->copy_oldpwd && ee->if_unset__oldpwd == 0)
		ft_printf("🏗️ 🏡 OLDPWD\n");
	else if (ee->copy_oldpwd && ft_strcmp(ee->copy_oldpwd, ee->copy_pwd) != 0
		&& ee->if_unset__oldpwd == 0)
		ft_printf("🏗️ 🏡 OLDPWD=%s\n", ee->copy_oldpwd);
	if (!ee->copy_pwd)
		ee->copy_pwd = getcwd(NULL, 0);
	if (ee->if_unset__pwd == 0)
		ft_printf("🏗️ 🏡 PWD=%s\n", ee->copy_pwd);
	if (ee->if_unset__shlvl == 0)
		ft_printf("🏗️ 🏡 SHLVL=1\n");
	free_split(args);
}

void	norminette_backstab(t_ee *ee, char **args)
{
	export_with_args(ee, args);
	check_if_path_is_not_modified(ee, args);
	check_if_path_is_set(ee, args);
	check_if_home_is_not_modified(ee, args);
	check_if_home_is_set(ee, args);
}

void	process_simple_export(char *input, t_ee *ee)
{
	char	**sorted_env;
	char	**concatene_both_tab;

	concatene_both_tab = NULL;
	input = parse_input_simple_export(input);
	if (ft_strcmp(input, "export") == 0)
		concatene_both_tab = copi_colle(ee);
	sorted_env = remove_duplicates_with_priority(concatene_both_tab);
	sort_export(ee, sorted_env);
	free_split(sorted_env);
	free_split(concatene_both_tab);
	free(input);
}
