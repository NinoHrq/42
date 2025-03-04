/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:36:41 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:36:42 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_path_dirs(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}

char	*construct_full_path(char *dir, char *command)
{
	char	temp_path[2024];

	temp_path[0] = '\0';
	ft_strcat(temp_path, dir);
	ft_strcat(temp_path, "/");
	ft_strcat(temp_path, command);
	return (ft_strdup(temp_path));
}

char	*search_command_in_dirs(char **dirs, char *command)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	while (dirs[i])
	{
		full_path = construct_full_path(dirs[i], command);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (full_path);
}

char	*find_command_path(char *command)
{
	char	**dirs;
	char	*full_path;

	if (command[0] == '.' || command[0] == '/')
		return (ft_strdup(command));
	dirs = get_path_dirs();
	if (!dirs)
		return (NULL);
	full_path = search_command_in_dirs(dirs, command);
	free_split(dirs);
	return (full_path);
}
