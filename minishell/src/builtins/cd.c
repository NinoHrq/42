#include "../../minishell.h"


char	*parse_input_cd(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';' && (input[i - 1] != ' '))
		{
			input[i] = '\0';
			break ;
		}
		i++;
	}
	return (input);
}

void ft_cd(char *input)
{
    char **args;
    char *home;
    char *cwd;
    int result;

    input = parse_input_cd(input);
    args = ft_split(input, ' ');
    if (args[1] == NULL || ft_strcmp(args[0], "~") == 0)
    {
        home = getenv("HOME");
        if (home == NULL)
        {
            printf("🍂_(´~`)_🍂: HOME not set\n");
            free_split(args);
            return;
        }
        result = chdir(home);
    }
    else
        result = chdir(args[1]);
    if (result != 0)
    {
        perror("🍂_(´~`)_🍂: cd");
        free_split(args);
        return;
    }
    cwd = getcwd(NULL, 0);
    if (cwd)
    {
        setenv("PWD", cwd, 1);
        free(cwd);
    }
    else
        perror("getcwd");
    free_split(args);
}

