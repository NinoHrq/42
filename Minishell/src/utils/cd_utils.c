/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:32:07 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:02:01 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	home_is_cooked(t_cd *cd)
{
	ft_printf("🍂_(´~`)_🍂: HOME not set\n");
	free_split(cd->args);
	free(cd);
}

void	careful_fire_burns(t_ee *ee, t_cd *cd)
{
	if (ee->copy_pwd)
		free(ee->copy_pwd);
	if (ee->copy_oldpwd)
		free(ee->copy_oldpwd);
	ee->change_confirmed = 1;
	ee->copy_oldpwd = getcwd(NULL, 0);
	cd->result = chdir(cd->args[1]);
	ee->copy_pwd = getcwd(NULL, 0);
	check_variable_pwd(ee);
}

void	am_i_cooked(char *input, t_cd *cd, t_ee *ee)
{
	input = parse_input_cd(input);
	cd->args = ft_split(input, ' ');
	ee->copy_oldpwd = getcwd(NULL, 0);
}

void	no_inspi_jutsu(t_cd *cd, t_ee *ee)
{
	cd->result = chdir(cd->home);
	if (ee->copy_pwd)
		free(ee->copy_pwd);
	ee->copy_pwd = getcwd(NULL, 0);
	check_variable_pwd(ee);
}

void	norminette_invocation(t_cd *cd)
{
	perror("🍂_(´~`)_🍂: cd");
	free_split(cd->args);
	free(cd);
}
