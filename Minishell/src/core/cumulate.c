/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cumulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:27:44 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 19:39:54 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_segment(char *segment, t_ee *ee)
{
	char	**changed_args;
	char	*input;
	int		result;

	changed_args = check_dollars(segment, ee);
	if (!changed_args)
		return (1);
	normalize_quotes(changed_args);
	input = reconstruct_input(changed_args);
	result = 0;
	if (find_parenthesis(segment) && found_single_or_double_quote(input) == 0)
		its_just_a_parenthese(segment, ee);
	else if (find_pipe(input) && !find_or(input) && !find_redirection(input))
		execute_pipeline(input, ee);
	else if (find_redirection_and_pipe(input)
		&& found_single_or_double_quote(input) == 0)
		execute_pipeline_heredoc(input, ee);
	else
		result = interprete_commande(input, ee);
	free_split(changed_args);
	free(input);
	return (result);
}

char	*copy_pasta(char *l, int *i, t_ee *ee)
{
	int		j;
	char	*copy;

	(void)ee;
	j = 0;
	copy = malloc(2048);
	if (!copy)
		return (NULL);
	while (l[*i] != '\0' && l[*i] != ';' && !(l[*i] == '&' && l[*i + 1] == '&'))
	{
		if (l[*i] == '(')
			copy_until_parenthesis(l, i, copy, &j);
		else if (l[*i] == '"' || l[*i] == '\'')
			copy_until_close_quote(l, i, copy, &j);
		else
		{
			copy[j++] = l[*i];
			(*i)++;
		}
	}
	copy[j] = '\0';
	return (copy);
}

bool	norminette_udertaker(bool success, t_ee *ee)
{
	success = false;
	ee->check_and_validity = 0;
	return (success);
}

bool	process_token(char *input, int *i, t_ee *ee, bool success)
{
	char	*copy;
	char	quote_type;

	copy = copy_pasta(input, i, ee);
	if (!copy)
		return (false);
	if (input[*i] == '"' || input[*i] == '\'')
	{
		quote_type = input[*i];
		(*i)++;
		while (input[*i] && input[*i] != quote_type)
			(*i)++;
		if (input[*i] == quote_type)
			(*i)++;
	}
	if (input[*i] == '&' && input[*i + 1] == '&')
		ee->command_with_and = 1;
	if (success)
		success = (process_segment(copy, ee) == 0);
	ee->command_with_and = 0;
	free(copy);
	if (ee->check_and_validity)
		success = norminette_udertaker(success, ee);
	return (success);
}

int	cumulate_token(char *input, t_ee *ee)
{
	int		i;
	bool	success;

	i = 0;
	success = true;
	while (input[i] != '\0')
	{
		success = process_token(input, &i, ee, success);
		if (input[i] == ';')
		{
			success = true;
			if (check_after_token(input, i) == 0)
				break ;
			i++;
		}
		if (input[i] == '&' && input[i + 1] == '&')
			i += 2;
	}
	return (0);
}
