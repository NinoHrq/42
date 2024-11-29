#include "../../minishell.h"

char	*parse_input_exit(char *input)
{
	int	i;

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

int	check_simple_exit(char *input)
{
	int i = 0;

	while(input[i] <= 32)
		i++;
	while(input[i] > 32)
		i++;
	while(input[i] <= 32)
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

	void ft_exit(char *input)
{
	char	**args;

	if (check_simple_exit(input) == 0)
	{
		ft_printf("🏃 exit\n");
		g_minishell_check = 1;
		return ;
	}
	input = parse_input_exit(input);
	args = ft_split(input, ' ');
	if (args[1] && !is_number(args[1]) && args[1][0] != ';')
	{
		ft_printf("exit\n");
		ft_printf("🚧_(⊙_⊙;)_🚧 : exit: %s: numeric argument required\n",
			args[1]);
		free_split(args);
		g_minishell_check = 1;
	}
	else if (args[2] != NULL && args[1][0] != ';' && args[2][0] != ';')
	{
		ft_printf("exit\n");
		ft_printf("💥_(╬ಠ益ಠ)_💥: exit: too many arguments\n");
	}
	else
	{
		ft_printf("🏃 exit\n");
		free_split(args);
		g_minishell_check = 1;
	}
}
