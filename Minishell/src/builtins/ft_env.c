/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:25:56 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:25:58 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_no_envp(t_ee *ee)
{
	if (ee->copy_pwd == NULL)
		ee->copy_pwd = getcwd(NULL, 0);
	if (ee->if_unset__pwd == 0)
		printf("🌱 PWD=%s\n", ee->copy_pwd);
	if (ee->if_unset__shlvl == 0)
		printf("🌱 SHLVL=1\n");
	printf("🌱 _=/usr/bin/env\n");
	if (ee->copy_oldpwd && ft_strcmp(ee->copy_oldpwd, ee->copy_pwd) != 0
		&& (ee->if_unset__oldpwd == 0))
		printf("🌱 OLDPWD=%s\n", ee->copy_oldpwd);
}

void	ft_env(t_ee *ee)
{
	int	i;

	if ((!ee->envp || !ee->envp[0]) && ee->lock_path == 0)
		if_no_envp(ee);
	else
	{
		i = 0;
		while (ee->envp[i])
		{
			if (ee->copy_oldpwd && (ee->envp[i + 1] == NULL)
				&& (ee->if_unset__oldpwd == 0))
				printf("🌱 OLDPWD=%s\n", ee->copy_oldpwd);
			printf("🌱 %s\n", ee->envp[i]);
			i++;
		}
	}
}
