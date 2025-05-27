/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:49:03 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/07 20:33:59 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quotesss(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	find_first_quote(char *arg)
{
	int	j;

	j = 0;
	if (!arg)
		return ('\0');
	while (arg[j])
	{
		if (arg[j] == '\'' || arg[j] == '"')
		{
			return (arg[j]);
		}
		j++;
	}
	return ('\0');
}

char	*remove_internal_quotes(char *arg, char quote)
{
	int		len;
	int		k;
	int		j;
	char	*new_str;

	len = strlen(arg);
	k = 0;
	j = 0;
	new_str = (char *)malloc(len + 3);
	while (arg[j])
	{
		if (arg[j] != '\'' && arg[j] != '"')
			new_str[k++] = arg[j];
		j++;
	}
	new_str[k] = '\0';
	if (quote != '\0')
	{
		memmove(new_str + 1, new_str, k);
		new_str[0] = quote;
		new_str[k + 1] = quote;
		k++;
	}
	new_str[k + 1] = '\0';
	return (new_str);
}

void	normalize_quotes(char **args)
{
	int		i;
	char	*new_str;
	char	quote;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		if (check_quotesss(args[i]))
		{
			quote = find_first_quote(args[i]);
			new_str = remove_internal_quotes(args[i], quote);
			if (new_str)
			{
				free(args[i]);
				args[i] = new_str;
			}
		}
		i++;
	}
}

/*void	normalize_quotes(char **args)
{
	char	*arg;
	int		len;
	char	quote;
	char	*new_str;
	int		k;

	if (!args)
		return ;

	for (int i = 0; args[i] != NULL; i++)
	{
		if (check_quotesss(args[i]))
		{
			arg = args[i];
			len = strlen(arg);
			if (len == 0)
				continue ;
			quote = '\0';
			for (int j = 0; j < len; j++)
			{
				if (arg[j] == '\'' || arg[j] == '"')
				{
					quote = arg[j];
					break ;
				}
			}
			new_str = (char *)malloc(len + 3);
			if (!new_str)
				return ;
			k = 0;
			for (int j = 0; j < len; j++)
			{
				if (arg[j] != '\'' && arg[j] != '"')
				{
					new_str[k++] = arg[j];
				}
			}
			if (quote != '\0')
			{
				memmove(new_str + 1, new_str, k);
				new_str[0] = quote;
				new_str[k + 1] = quote;
				k++;
			}
			new_str[k + 1] = '\0';
			free(args[i]);
			args[i] = new_str;
		}
	}
}*/
