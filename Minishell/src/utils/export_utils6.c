/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:09 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:34:10 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	count_arguments(t_ewa *ewa, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_check_equal(args[i]))
			ewa->count_equal++;
		else
			ewa->count_args_without_equal++;
		i++;
	}
}

void	allocate_and_copy_envp(t_ewa *ewa, t_ee *ee)
{
	int	i;

	i = 0;
	if (ee->envp)
	{
		while (ee->envp[ewa->len_envp])
			ewa->len_envp++;
		ewa->copy_envp = malloc(sizeof(char *) * (ewa->len_envp
					+ ewa->count_equal + 1));
		while (i < ewa->len_envp)
		{
			ewa->copy_envp[i] = ft_strdup(ee->envp[i]);
			i++;
		}
		ewa->copy_envp[ewa->len_envp] = NULL;
	}
	else
		ewa->copy_envp = malloc(sizeof(char *) * (ewa->count_equal + 1));
}

void	allocate_and_copy_export(t_ewa *ewa, t_ee *ee)
{
	int	i;

	i = 0;
	if (ee->copy_export_env)
	{
		while (ee->copy_export_env[ewa->len_export])
			ewa->len_export++;
		ewa->copy_export = malloc(sizeof(char *) * (ewa->len_export
					+ ewa->count_args_without_equal + 1));
		while (i < ewa->len_export)
		{
			ewa->copy_export[i] = ft_strdup(ee->copy_export_env[i]);
			i++;
		}
	}
	else if (ewa->count_args_without_equal > 0)
		ewa->copy_export = malloc(sizeof(char *)
				* (ewa->count_args_without_equal + 1));
	if (ewa->copy_export)
		ewa->copy_export[ewa->len_export] = NULL;
}

void	export_with_args(t_ee *ee, char **args)
{
	t_ewa	ewa;

	initialize_ewa(&ewa);
	count_arguments(&ewa, args);
	allocate_and_copy_envp(&ewa, ee);
	allocate_and_copy_export(&ewa, ee);
	handle_env_with_equals(args, &ewa.copy_envp, &ewa.len_envp);
	handle_export_without_equals(args, &ewa.copy_export, &ewa.len_export);
	free_split(ee->envp);
	ee->envp = ewa.copy_envp;
	free_split(ee->copy_export_env);
	ee->copy_export_env = ewa.copy_export;
}

/*void export_with_args(t_ee *ee, char **args)
{
	char **copy_envp = NULL;
	char **copy_export = NULL;
	int len_envp = 0, len_export = 0;
	int count_equal = 0, count_args_without_equal = 0;

	int i = 1;
	while (args[i])
	{
		if (ft_check_equal(args[i]))
			count_equal++;
		else
			count_args_without_equal++;
		i++;
	}
	if (ee->envp)
	{
		while (ee->envp[len_envp])
			len_envp++;
		copy_envp = malloc(sizeof(char *) * (len_envp + count_equal + 1));
		i = 0;
		while (i < len_envp)
		{
			copy_envp[i] = ft_strdup(ee->envp[i]);
			i++;
		}
		copy_envp[len_envp] = NULL;
	}
	else
		copy_envp = malloc(sizeof(char *) * (count_equal + 1));
	if (ee->copy_export_env)
	{
		while (ee->copy_export_env[len_export])
			len_export++;
		copy_export = malloc(sizeof(char *) * (len_export
					+ count_args_without_equal + 1));
		i = 0;
		while (i < len_export)
		{
			copy_export[i] = ft_strdup(ee->copy_export_env[i]);
			i++;
		}
	}
	else if (count_args_without_equal > 0)
		copy_export = malloc(sizeof(char *) * (count_args_without_equal + 1));
	if (copy_export)
		copy_export[len_export] = NULL;
	handle_env_with_equals(args, &copy_envp, &len_envp);
	handle_export_without_equals(args, &copy_export, &len_export);
	free_split(ee->envp);
	ee->envp = copy_envp;
	free_split(ee->copy_export_env);
	ee->copy_export_env = copy_export;
}*/
