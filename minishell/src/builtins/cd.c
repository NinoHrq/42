#include "../../minishell.h"

char	*parse_input_cd(char *input)
{
	int i = 0;

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

void	ft_cd(char *input, t_ee *ee)
{
	t_cd *cd;
	int result;

	cd = malloc(sizeof(t_cd));
	input = parse_input_cd(input);
	cd->args = ft_split(input, ' ');
	ee->copy_oldpwd = getcwd(NULL, 0);
	if (cd->args[1] == NULL || ft_strcmp(cd->args[0], "~") == 0)
	{
		ee->change_confirmed = 1;
		cd->home = getenv("HOME");
		if (cd->home == NULL)
		{
			printf("🍂_(´~`)_🍂: HOME not set\n");
			free_split(cd->args);
			free(cd);
			return ;
		}
		else
		{
			result = chdir(cd->home);
			if (ee->copy_pwd)
				free(ee->copy_pwd);
			ee->copy_pwd = getcwd(NULL, 0);
			check_variable_pwd(ee);
		}
	}
	else
	{
		if (ee->copy_pwd)
			free(ee->copy_pwd);
		if (ee->copy_oldpwd)
			free(ee->copy_oldpwd);
		ee->change_confirmed = 1;
		ee->copy_oldpwd = getcwd(NULL, 0);
		result = chdir(cd->args[1]);
		ee->copy_pwd = getcwd(NULL, 0);
		check_variable_pwd(ee);
	}
	if (result != 0)
	{
		perror("🍂_(´~`)_🍂: cd");
		free_split(cd->args);
		free(cd);
		return ;
	}
	free_split(cd->args);
	free(cd);
}

int	ft_strcmpchar(char a, char b)
{
	if (a != b)
		return (1);
	return (0);
}

void	check_variable_pwd(t_ee *ee)
{
	int i = 0;
	int j;
	int yes = 0;

	// ft_printf("%s\n", ee->envp[i]);
	while (ee->envp[i])
	{
		j = 0;
		while (ee->envp[i][j])
		{
			// ft_printf("%c", ee->envp[i][j]);
			if ((ft_strcmpchar(ee->envp[i][j], 'P') == 0)
				&& (ft_strcmpchar(ee->envp[i][j + 1], 'W') == 0)
				&& (ft_strcmpchar(ee->envp[i][j + 2], 'D') == 0))
			{
				yes = 1;
				break ;
			}
			j++;
		}
		if (yes == 1)
			break ;
		i++;
	}
	// ft_printf("%s\n", ee->envp[i]);
	char *copy = ft_strjoin_cd("PWD=", ee->copy_pwd);
	if (!copy)
		return ;
	// ft_printf("%s\n", copy);
	if (ee->envp[i] && ((ft_strcmp(ee->envp[i], ee->copy_pwd) != 0)
			|| (ft_strcmp(ee->envp[i], ee->copy_pwd) == 0)))
	{
		free(ee->envp[i]);
		ee->envp[i] = ft_strdup(copy);
	}
	free(copy);
	// ft_printf("%s\n", ee->envp[i]);
}

char	*ft_strjoin_cd(char *s1, char *s2)
{
	char *res;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	// free(s1);
	return (res);
}
