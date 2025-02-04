#include "../../minishell.h"

void	ft_echo(char *input)
{
	char	**args;
	bool	no_newline;
	int		i;

	no_newline = false;
	i = 1;
	args = ft_split(input, ' ');
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		no_newline = true;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!no_newline)
		ft_printf("\n");
	free_split(args);
}
