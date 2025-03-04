/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:37:02 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:37:03 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_variable(char *input, t_ee *ee)
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

void	path_confirm(char *input)
{
	char	**check_path;
	char	*path;

	check_path = ft_split(input, ' ');
	path = find_command_path(check_path[0]);
	if (!path)
		ft_printf("🍁_(`へ´*)_🍁: %s: command not found\n", check_path[0]);
	free_split(check_path);
	if (path)
		free(path);
}

void	path_checker(char *input, t_ee *ee)
{
	char	**check_path;
	char	*path;

	if (!input)
		return ;
	check_path = ft_split(input, ' ');
	path = find_command_path(check_path[calcul_check_path(check_path)]);
	if (!path)
	{
		ee->signal = 127;
		ee->check_and_validity = 1;
		ee->confirmed_command = 0;
	}
	else
	{
		ee->signal = 0;
		ee->check_and_validity = 0;
		ee->confirmed_command = 1;
	}
	free_split(check_path);
	if (path)
		free(path);
	if (input)
		free(input);
}

void	check_if_path_is_set(t_ee *ee, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "PATH=/bin:/usr/bin") == 0
			|| (ee->save_initial_path && ft_strcmp(args[i],
					ee->save_initial_path) == 0))
		{
			setenv("PATH", "/bin:/usr/bin", 1);
			ee->lock_path = 0;
			ee->path_is_not_able = 0;
			break ;
		}
		i++;
	}
}

/*char	*find_command_path(char *command)
{
	char	*path_env;
	char	**dirs;
	char	*full_path;
	int		i;
	char	temp_path[2024];

	i = 0;
	if (command[i] == '.' || command[i] == '/')
		return(ft_strdup(command));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	full_path = NULL;
	while (dirs[i])
	{
		temp_path[0] = '\0';
		ft_strcat(temp_path, dirs[i]);
		ft_strcat(temp_path, "/");
		ft_strcat(temp_path, command);
		if (access(temp_path, X_OK) == 0)
		{
			full_path = ft_strdup(temp_path);
			break ;
		}
		i++;
	}
	free_split(dirs);
	return (full_path);
}*/
