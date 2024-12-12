#include "../../minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void	ft_echo(char *input)
{
	char	**args;
	bool	no_newline;
	int		i;

	no_newline = false;
	i = 1;
	args = ft_split(input, ' ');
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		no_newline = true;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	free_split(args);
}
