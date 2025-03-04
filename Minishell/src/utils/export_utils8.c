/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:25 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:34:26 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sort_sorted_env(char **sorted_env, int len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp_dif(sorted_env[i], sorted_env[j]) > 0)
			{
				tmp = sorted_env[i];
				sorted_env[i] = sorted_env[j];
				sorted_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	add_oldpwd(t_ee *ee, char **sorted_env, int *len)
{
	char	*oldpwd;

	if (ee->copy_oldpwd)
	{
		oldpwd = ft_strcat_export("OLDPWD=", ee->copy_oldpwd);
		if (oldpwd)
		{
			sorted_env[*len] = oldpwd;
			(*len)++;
		}
	}
	else
	{
		oldpwd = ft_strdup("OLDPWD");
		sorted_env[*len] = oldpwd;
		(*len)++;
	}
}

void	copy_sorted_elements(char **sorted, char **sorted_env, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		sorted_env[i] = ft_strdup(sorted[i]);
		i++;
	}
}

int	calculate_sorted_len(char **sorted, t_ee *ee)
{
	int	len;

	len = 0;
	while (sorted[len])
		len++;
	if (ee->copy_oldpwd)
		len++;
	return (len);
}

void	sort_export(t_ee *ee, char **sorted)
{
	char	**sorted_env;
	int		len;

	len = 0;
	len = calculate_sorted_len(sorted, ee);
	sorted_env = malloc(sizeof(char *) * (len + 1));
	if (!sorted_env)
		return ;
	copy_sorted_elements(sorted, sorted_env, len);
	add_oldpwd(ee, sorted_env, &len);
	sort_sorted_env(sorted_env, len);
	print_and_free_sorted_env(sorted_env, len);
}

/*void	sort_export(t_ee *ee, char **sorted)
{
	char **sorted_env;
	int len = 0;
	int i, j;
	char *tmp;
	char *oldpwd;

	while (sorted[len])
		len++;
	sorted_env = malloc(sizeof(char *) * (len + 2));
	if (!sorted_env)
		return ;
	i = 0;
	while (i < len)
	{
		sorted_env[i] = ft_strdup(sorted[i]);
		i++;
	}
	if (ee->copy_oldpwd)
	{
		oldpwd = ft_strcat_export("OLDPWD=", ee->copy_oldpwd);
		if (oldpwd)
		{
			sorted_env[len] = oldpwd;
			len++;
		}
	}
	else
	{
		oldpwd = ft_strdup("OLDPWD");
		sorted_env[len] = oldpwd;
		len++;
	}
	sorted_env[len] = NULL;
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp_dif(sorted_env[i], sorted_env[j]) > 0)
			{
				tmp = sorted_env[i];
				sorted_env[i] = sorted_env[j];
				sorted_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < len)
	{
		if (sorted_env[i])
			ft_printf("🏗️ 🏡 %s\n", sorted_env[i]);
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}*/
