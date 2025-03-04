/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:49:03 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:49:15 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_normalizer(t_quote_normalizer *q)
{
	q->i = 0;
	q->quote_type = '\0';
	q->k = 0;
}

int	check_quotes(char *arg, t_quote_normalizer *q)
{
	int	len;

	len = strlen(arg);
	if (len >= 2 && (arg[0] == '"' || arg[0] == '\'') && arg[0] == arg[len - 1])
	{
		q->quote_type = arg[0];
		return (1);
	}
	return (0);
}

void	process_quotes(char *arg, t_quote_normalizer *q)
{
	int	len;

	len = strlen(arg);
	q->result[q->k++] = arg[0];
	q->j = 1;
	while (q->j < len - 1)
	{
		if ((q->quote_type == '"' && arg[q->j] == '\'')
			|| (q->quote_type == '\'' && arg[q->j] == '"'))
		{
			q->j++;
			continue ;
		}
		q->result[q->k++] = arg[q->j];
		q->j++;
	}
	q->result[q->k++] = arg[len - 1];
	q->result[q->k] = '\0';
}

void	normalize_quotes(char **args)
{
	t_quote_normalizer	q;

	init_normalizer(&q);
	while (args[q.i])
	{
		if (check_quotes(args[q.i], &q))
		{
			process_quotes(args[q.i], &q);
			strcpy(args[q.i], q.result);
		}
		q.i++;
	}
}

/*void normalize_quotes(char **args)
{
	int i = 0;
	while (args[i])
	{
		int j = 0, k = 0;
		char quote_type = '\0';
		char result[2048];
		int len = strlen(args[i]);
		if (len >= 2 && (args[i][0] == '"' || args[i][0] == '\'')
				&& args[i][0] == args[i][len - 1])
			quote_type = args[i][0];
		if (quote_type)
		{
			result[k++] = args[i][0];
			for (j = 1; j < len - 1; j++)
			{
				if ((quote_type == '"' && args[i][j] == '\'') ||
					(quote_type == '\'' && args[i][j] == '"'))
					continue ;
				result[k++] = args[i][j];
			}
			result[k++] = args[i][len - 1];
			result[k] = '\0';
			strcpy(args[i], result);
		}
		i++;
	}
}*/
