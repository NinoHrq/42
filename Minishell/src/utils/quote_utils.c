/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:37:15 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:37:16 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_env_var(const char *var_name, t_ee *ee)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(var_name);
	while (ee->envp && ee->envp[i])
	{
		if (ft_strncmp(ee->envp[i], var_name, name_len) == 0
			&& ee->envp[i][name_len] == '=')
			return (ft_strdup(&ee->envp[i][name_len + 1]));
		i++;
	}
	return (NULL);
}

int	handle_expansion(t_quote_handler *qh, char *input, t_ee *ee)
{
	char	*expanded;
	int		expanded_len;

	expanded = expand_variable(&input[qh->i], ee);
	if (!expanded)
		return (0);
	expanded_len = ft_strlen(expanded);
	if (qh->j + expanded_len >= qh->size)
	{
		qh->size *= 2;
		qh->result = realloc(qh->result, qh->size);
		if (!qh->result)
		{
			free(expanded);
			return (0);
		}
	}
	strcpy(&qh->result[qh->j], expanded);
	qh->j += expanded_len;
	free(expanded);
	qh->i++;
	while (input[qh->i] && (ft_isalnum(input[qh->i]) || input[qh->i] == '_'))
		qh->i++;
	return (1);
}

void	expand_buffer_if_needed(t_quote_handler *qh)
{
	if (qh->j + 1 >= qh->size)
	{
		qh->size *= 2;
		qh->result = realloc(qh->result, qh->size);
	}
}

char	*handle_quotes(char *input, t_ee *ee)
{
	t_quote_handler	qh;

	init_quote_handler(&qh);
	if (!qh.result)
		return (NULL);
	while (input[qh.i])
	{
		if ((input[qh.i] == '\'') && qh.quote == '\0')
			qh.quote = input[qh.i++];
		else if (input[qh.i] == qh.quote)
		{
			qh.quote = '\0';
			qh.i++;
		}
		else
		{
			if (qh.quote == '"' && input[qh.i] == '$' && handle_expansion(&qh,
					input, ee))
				continue ;
			expand_buffer_if_needed(&qh);
			qh.result[qh.j++] = input[qh.i++];
		}
	}
	qh.result[qh.j] = '\0';
	return (qh.result);
}

/*char *expand_variable(char *input, t_ee *ee)
{
	char	var_name[256];
	int		i;
	int		j;
	char	*value;

	i = 1;
	j = 0;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
	{
		if (j < 255)
			var_name[j++] = input[i++];
	}
	var_name[j] = '\0';
	value = find_env_var(var_name, ee);
	if (value)
		return (value);
	return (ft_strdup(""));
}

char	*handle_quotes(char *input, t_ee *ee)
{
	char *result = malloc(1024);
	int size = 1024;
	int i = 0, j = 0;
	char quote = '\0';
	char *expanded;
	int expanded_len;

	if (!result)
		return (NULL);
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && quote == '\0')
			quote = input[i++];
		else if (input[i] == quote)
		{
			quote = '\0';
			i++;
		}
		else
		{
			if (quote == '"' && input[i] == '$')
			{
				expanded = expand_variable(&input[i], ee);
				if (expanded)
				{
					expanded_len = ft_strlen(expanded);
					if (j + expanded_len >= size)
					{
						size *= 2;
						result = realloc(result, size);
						if (!result) {
							free(expanded);
							return (NULL);
						}
					}
					strcpy(&result[j], expanded);
					j += expanded_len;
					free(expanded);
					i++;
					while (input[i] && (ft_isalnum(input[i])
							|| input[i] == '_'))
						i++;
					continue ;
				}
			}
			if (j + 1 >= size)
			{
				size *= 2;
				result = realloc(result, size);
				if (!result)
					return (NULL);
			}
			result[j++] = input[i++];
		}
	}
	result[j] = '\0';
	return (result);
}*/
