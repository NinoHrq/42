/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:33:32 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:33:33 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_invalid_identifier(const char *arg)
{
	ft_printf("🔥_(╬ Ò﹏Ó)_🔥: export: %s: not a valid identifier\n", arg);
}

size_t	get_key_length(const char *arg)
{
	return (ft_strchr(arg, '=') - arg);
}

void	allocate_result(t_rdp *rdp)
{
	rdp->i = 0;
	while (rdp->i < rdp->len_env)
	{
		if (rdp->to_keep[rdp->i])
			rdp->new_len++;
		rdp->i++;
	}
	rdp->result = malloc(sizeof(char *) * (rdp->new_len + 1));
}

void	print_and_free_sorted_env(char **sorted_env, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (sorted_env[i])
			ft_printf("🏗️ 🏡 %s\n", sorted_env[i]);
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}
