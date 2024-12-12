#include "../../minishell.h"

char	*parse_input_exit(char *input, t_token *exit)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';' && input[i + 1] == ';')
			exit->token = 1;
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
	int	i;

	i = 0;
	while (input[i] <= 32)
		i++;
	while (input[i] > 32)
		i++;
	return (0);
}

void	ft_exit(char *input, t_ee *ee)
{
	t_token	*exit;
	char	**args;

	exit = malloc(sizeof(t_token));
	exit->token = 0;
	input = parse_input_exit(input, exit);
	args = ft_split(input, ' ');
	if (check_simple_exit(input) == 0 && args[1] == NULL)
	{
		ft_printf("🏃 exit\n");
		if (args)
			free_split(args);
		free(exit);
		ee->minishell_check = 1;
		return ;
	}
	if (exit->token == 1)
	{
		printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;'\n");
		return ;
	}
	if (args[1] && !is_number(args[1]) && args[1][0] != ';')
	{
		ft_printf("exit\n");
		ft_printf("🚧_(⊙_⊙;)_🚧 : exit: %s: numeric argument required\n",
			args[1]);
		free_split(args);
		free(exit);
		ee->minishell_check = 1;
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
		free(exit);
		ee->minishell_check = 1;
	}
}
