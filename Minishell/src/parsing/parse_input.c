/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:30:35 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:30:36 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*reconstruct_input(char **changed_args)
{
	t_reconstruct	data;

	data.i = 0;
	data.total_len = 0;
	while (changed_args[data.i])
	{
		data.total_len += ft_strlen(changed_args[data.i]) + 1;
		data.i++;
	}
	data.new_input = malloc(sizeof(char) * data.total_len);
	if (!data.new_input)
		return (NULL);
	data.current_pos = data.new_input;
	data.i = 0;
	while (changed_args[data.i])
	{
		data.len = ft_strlen(changed_args[data.i]);
		memcpy(data.current_pos, changed_args[data.i], data.len);
		data.current_pos += data.len;
		if (changed_args[data.i + 1])
			*data.current_pos++ = ' ';
		data.i++;
	}
	*data.current_pos = '\0';
	return (data.new_input);
}

char	*parse_input_pipeline(char *input)
{
	t_pipeline_parser	p;

	p.i = 0;
	p.j = 0;
	p.extra_spaces = count_extra_spaces_pipeline(input);
	p.tmp = malloc(sizeof(char) * (strlen(input) + p.extra_spaces + 1));
	if (!p.tmp)
		return (NULL);
	while (input[p.i])
	{
		if (input[p.i] == '|')
		{
			if (p.j > 0 && p.tmp[p.j - 1] > 32)
				p.tmp[p.j++] = ' ';
			p.tmp[p.j++] = '|';
			if (input[p.i + 1] && input[p.i + 1] > 32)
				p.tmp[p.j++] = ' ';
		}
		else
			p.tmp[p.j++] = input[p.i];
		p.i++;
	}
	p.tmp[p.j] = '\0';
	return (p.tmp);
}

char	*parse_exev_input(char *tmp_in)
{
	int		i;
	int		j;
	char	*return_input;

	i = 0;
	j = 0;
	while (tmp_in && tmp_in[i])
	{
		if (tmp_in[i] == '>' || tmp_in[i] == '<')
			break ;
		i++;
	}
	return_input = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		return_input[j] = tmp_in[j];
		j++;
	}
	return_input[j] = '\0';
	return (return_input);
}

char	*parse_input_exit(char *input, t_token *exit)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';' && input[i + 1] == ';')
			exit->token = 1;
		if (input[i] == ';' && (input[i - 1] != ' '))
		{
			input[i] = '\0';
			break ;
		}
		i++;
	}
	return (input);
}

char	*parse_input_cd(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == ';' && i > 0 && input[i - 1] != ' ')
		{
			input[i] = '\0';
			break ;
		}
		i++;
	}
	return (input);
}

/*char	*reconstruct_input(char **changed_args)
{
	int		i;
	size_t	total_len;
	char	*new_input;
	char	*current_pos;
	size_t	len;

	i = 0;
	total_len = 0;
	while (changed_args[i])
	{
		total_len += ft_strlen(changed_args[i]) + 1;
		i++;
	}
	new_input = malloc(sizeof(char) * total_len);
	if (!new_input)
		return (NULL);
	current_pos = new_input;
	i = 0;
	while (changed_args[i])
	{
		len = ft_strlen(changed_args[i]);
		ft_memcpy(current_pos, changed_args[i], len);
		current_pos += len;
		if (changed_args[i + 1])
			*current_pos++ = ' ';
		i++;
	}
	*current_pos = '\0';
	return (new_input);
}*/

/*char *parse_input_pipeline(char *input)
{
	int i = 0, j = 0, count = 0;
	char *tmp;

	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (i > 0 && input[i - 1] > 32)
				count++;
			if (input[i + 1] && input[i + 1] > 32)
				count++;
		}
		i++;
	}
	tmp = malloc(sizeof(char) * (i + count + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (j > 0 && tmp[j - 1] > 32)
				tmp[j++] = ' ';
			tmp[j++] = '|';
			if (input[i + 1] && input[i + 1] > 32)
				tmp[j++] = ' ';
		}
		else
			tmp[j++] = input[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}*/

/*char *remove_parentheses(char *input)
{
	int i = 0, j = 0, level = 0;
	char *tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!tmp)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '(')
		{
			if (level > 0)
				tmp[j++] = input[i];
			level++;
		} else if (input[i] == ')')
		{
			level--;
			if (level > 0)
				tmp[j++] = input[i];
		}
		else
		{
			if (level > 0 || (level == 0 && input[i] != ')'))
				tmp[j++] = input[i];
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}*/
