/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_or_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:28:35 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:28:36 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_confirmed_command_equal_to_zero(char *command_after_or, t_ee *ee)
{
	if (command_after_or != NULL)
		cumulate_token(command_after_or, ee);
	if (ee->confirmed_command == 1 || ee->save_result == 1)
		ee->check_and_validity = 0;
	else
	{
		ee->check_and_validity = 1;
	}
}

char	*parse_command_after(char *command_after_or)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	k = ft_strlen(command_after_or);
	while (command_after_or[i] && command_after_or[i] <= 32)
		i++;
	j = 0;
	tmp = malloc(sizeof(char) * (k - i + 1));
	while (command_after_or[i])
	{
		tmp[j++] = command_after_or[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

void	check_valid_after(char *command_after_or, t_ee *ee)
{
	char	*path;
	char	*tmp_after;

	tmp_after = parse_command_after(command_after_or);
	path = find_command_path(tmp_after);
	if (path)
		ee->save_result = 1;
	else
		ee->save_result = 0;
	free(tmp_after);
	free(path);
}

void	after_find_or(char *input, t_ee *ee)
{
	char	*command_before_or;
	char	*command_after_or;
	char	*see_what_after;

	command_after_or = NULL;
	if (check_after_or(input) == 0)
	{
		command_before_or = copy_before_or(input);
		command_after_or = copy_after_or(input);
		see_what_after = copy_after_or(command_after_or);
		if (see_what_after == NULL)
			check_valid_after(command_after_or, ee);
		free(see_what_after);
		cumulate_token(command_before_or, ee);
		if (ee->confirmed_command == 0)
			if_confirmed_command_equal_to_zero(command_after_or, ee);
		free_after_or(command_before_or, command_after_or, ee);
		return ;
	}
}

int	handle_or_and_redirection(char *input, t_ee *ee)
{
	if (find_or(input) == 1 && found_single_or_double__(input) == 1)
	{
		after_find_or(input, ee);
		return (1);
	}
	if (find_redirection(input) == 1 && found_single__(input) == 1)
	{
		handle_redirection(input, ee);
		return (1);
	}
	return (0);
}
