/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:32:27 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:32:29 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_exit_syntax_error(void)
{
	ft_printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;'\n");
}

void	handle_exit_numeric_error(char **args, t_ee *ee, t_token *exit)
{
	ft_printf("🏃 exit\n");
	ft_printf("🚧_(⊙_⊙;)_🚧 : exit: %s: numeric argument required\n", args[1]);
	free_split(args);
	free(exit);
	ee->code_exit = 2;
	ee->minishell_check = 1;
}
