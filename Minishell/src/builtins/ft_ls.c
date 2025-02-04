#include "../../minishell.h"

char	*parse_input_ls(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';' && input[i + 1] == '\0')
		{
			input[i] = '\0';
			break ;
		}
		if (input[i] == ';' && input[i + 1] != '\0')
		{
			input[i] = '\0';
			break ;
		}
		if (input[i] == ';' && (input[i - 1] != ' '))
		{
			input[i] = '\0';
			break ;
		}
		i++;
	}
	return (input);
}

void	ft_ls(char *input)
{
	char			**args;
	char			*path;
	DIR				*dir;
	int				file_found;
	struct dirent	*entry;

	file_found = 0;
	input = parse_input_ls(input);
	args = ft_split(input, ' ');
	if (args[1] == NULL)
	{
		path = ".";
		dir = opendir(path);
	}
	else
		dir = opendir(args[1]);
	if (!dir)
	{
		printf("💔_(ಥ﹏ಥ)_💔: cannot access '%s': No such file or directory\n",
			args[1]);
		return ;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			printf("%s ", entry->d_name);
			file_found = 1;
		}
	}
	if (file_found)
		printf("\n");
	free_split(args);
	closedir(dir);
}
