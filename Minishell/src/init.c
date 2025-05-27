/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:24:19 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/04 19:45:09 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_status = 0;

void	init_struct(t_ee *ee)
{
	ee->single_quote = 0;
	ee->error_exit = 0;
	ee->reset_sigint = 0;
	ee->code_exit = 0;
	ee->minishell_check = 0;
	ee->change_confirmed = 0;
	ee->copy_pwd = NULL;
	ee->copy_oldpwd = NULL;
	ee->if_unset__pwd = 0;
	ee->if_unset__oldpwd = 0;
	ee->if_unset__shlvl = 0;
	ee->lock_path = 0;
	ee->copy_export_env = NULL;
	ee->path_is_not_able = 0;
	ee->save_initial_path = NULL;
	ee->check_and_validity = 0;
	ee->command_with_and = 0;
	ee->command_with_or = 0;
	ee->confirmed_command = 0;
	ee->signal = 0;
	ee->save_result = 0;
	ee->block_home = 0;
	ee->copy_home = NULL;
}
