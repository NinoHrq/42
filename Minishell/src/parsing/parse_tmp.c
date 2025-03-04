/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:31:14 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:31:15 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_syntax_at_start(const char *t, t_ee *ee)
{
	int	i;

	i = skip_whitespace(t);
	if (t[i] == '&')
	{
		if ((t[i + 1] == '&' && t[i + 2] == '&') || (t[i] == '&' && t[i
					+ 1] != '&'))
			printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `&'\n");
		else if (t[i + 1] == '&')
			printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `&&'\n");
		ee->signal = 2;
		return (1);
	}
	if (t[i] == '|')
	{
		if ((t[i + 1] == '|' && t[i + 2] == '|') || (t[i] == '|' && t[i
					+ 1] != '|'))
			printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `|'\n");
		else if (t[i + 1] == '|')
			printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `||'\n");
		ee->signal = 2;
		return (1);
	}
	return (0);
}

int	check_syntax_in_body(const char *tmp, t_ee *ee)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '&' && tmp[i + 1] == '&' && tmp[i + 2] == '&')
		{
			for_norminette(ee);
			return (1);
		}
		if (tmp[i] == '|' && tmp[i + 1] == '|' && tmp[i + 2] == '|')
		{
			printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `|'\n");
			ee->signal = 2;
			return (1);
		}
		if (tmp[i] == ';' && tmp[i + 1] == ';')
		{
			printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;'\n");
			ee->signal = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_syntax_error(const char *tmp, t_ee *ee)
{
	if (check_syntax_at_start(tmp, ee))
		return (1);
	return (check_syntax_in_body(tmp, ee));
}

int	check_unexpected_semicolon(char *tmp, t_ee *ee)
{
	int	i;

	i = skip_whitespacee(tmp, 0);
	if (tmp[i] == ';')
	{
		i++;
		i = skip_whitespacee(tmp, i);
		if (tmp[i] == '\0')
		{
			printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;'\n");
			ee->signal = 2;
			return (1);
		}
	}
	return (0);
}

int	find_trap(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] && input[i] != ';')
		i++;
	if (input[i] == ';')
	{
		i++;
		while (input[i] && input[i] <= 32)
			i++;
		if (input[i] == ';')
		{
			printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;'\n");
			return (1);
		}
	}
	return (0);
}
