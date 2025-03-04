/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:35:51 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:35:53 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	initialize_ewa(t_ewa *ewa)
{
	ewa->copy_envp = NULL;
	ewa->copy_export = NULL;
	ewa->len_envp = 0;
	ewa->len_export = 0;
	ewa->count_equal = 0;
	ewa->count_args_without_equal = 0;
}

void	initialize_rdp(t_rdp *rdp)
{
	rdp->i = 0;
	rdp->j = 0;
	rdp->k = 0;
	rdp->len_env = 0;
	rdp->name_i_len = 0;
	rdp->name_j_len = 0;
	rdp->new_len = 0;
	rdp->to_keep = NULL;
	rdp->result = NULL;
	rdp->name_i = NULL;
	rdp->name_j = NULL;
}

void	assign_rdp_name(t_rdp *rdp, char **env)
{
	rdp->name_i_len = ft_strcspn(env[rdp->i], "=");
	rdp->name_j_len = ft_strcspn(env[rdp->j], "=");
	rdp->name_i = ft_strndup(env[rdp->i], rdp->name_i_len);
	rdp->name_j = ft_strndup(env[rdp->j], rdp->name_j_len);
}

void	init_varex(t_varex *v)
{
	v->i = 0;
	v->k = 0;
	v->j = 0;
}
