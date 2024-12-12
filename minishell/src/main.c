#include "../minishell.h"

int		g_omg_le_plus_beau_du_tieks_ca_dit_koi_le_sang_trkl_la_bess_j_ai_vu_tu_connais_ici_c_est_la_debrouille;

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		else
			i++;
	}
	return (0);
}
//    utils.c    /////////////////////////////////////////

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*skip_isspace_for_fonctions(char *input, t_token *token)
{
	char	*s;
	int		i;

	i = 0;
	if (check_token(input, token) == 1)
		return (";");
	else
	{
		s = malloc(sizeof(char) * ft_strlen(input) + 1);
		while (*input <= 32)
			input++;
		while (*input > 32)
		{
			s[i] = *input;
			i++;
			input++;
		}
		s[i] = '\0';
	}
	return (s);
}

int	check_token_in_all_string(char *input, t_token *tok)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';')
		{
			if (input[i + 1] == ';')
				return (1);
			while (input[i + 1] <= 32)
				i++;
			if (input[i + 1] == ';')
			{
				tok->token = 2;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_token(char *input, t_token *token)
{
	int	i;

	i = 0;
	while (input[i] <= 32)
		i++;
	if (input[i] == ';' && input[i + 1] != ';')
	{
		token->token = 1;
		return (1);
	}
	return (0);
}

int	token_found(char *input, t_token *tok)
{
	int	i;

	i = 0;
	while (input[i] <= 32)
		i++;
	if (input[i] == '\0')
		return (0);
	while (input[i])
	{
		if (input[i] == ';' && input[i + 1] == '\0')
			return (0);
		if (input[i] == ';' && input[i + 1] != '\0')
		{
			tok->found = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

////////////////////////////////////////////////////////

void	execute_external_command(char *command);

void	interprete_commande(char *input, t_ee *ee)
{
	char	*trimmed_input;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->token = 0;
	trimmed_input = skip_isspace_for_fonctions(input, token);
	if (!trimmed_input)
	{
		free(token);
		return ;
	}
	if (token->token == 1)
	{
		printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token ';'\n");
		free(token);
		return ;
	}
	else if (ft_strcmp(trimmed_input, "exit") == 0)
	{
		if (ft_strcmp(trimmed_input, "exit") == 0 && ft_strcmp(trimmed_input,
				input) == 0)
		{
			printf("🏃 exit\n");
			ee->minishell_check = 1;
		}
		else
			ft_exit(input, ee);
	}
	else if (ft_strcmp(trimmed_input, "pwd") == 0)
		ft_pwd();
	else if ((ft_strcmp(trimmed_input, "cd") == 0) || (ft_strcmp(trimmed_input,
				"~") == 0))
	{
		if (ee->copy_oldpwd)
			free(ee->copy_oldpwd);
		if (ee->copy_pwd)
			free(ee->copy_pwd);
		ft_cd(input, ee);
	}
	// else if (ft_strcmp(trimmed_input, "ls") == 0)
	//	ft_ls(input);
	// else if (ft_strcmp(trimmed_input, "clear") == 0)
	//	ft_clear(input);
	else if (ft_strcmp(trimmed_input, "env") == 0)
		ft_env(ee);
	else if (ft_strcmp(trimmed_input, "wc") == 0)
		ft_wc(input);
	else if (ft_strcmp(trimmed_input, "unset") == 0)
		ft_unset(input, ee);
	else if ((ft_strcmp(trimmed_input, "export") == 0)
		|| (ft_strcmp(trimmed_input, "export=") == 0))
		ft_export(input, ee);
	else if (ft_strcmp(trimmed_input, "echo") == 0)
		ft_echo(input);
	else
	{
		if (ee->minishell_check == 0)
			execute_external_command(input);
	}
	free(token);
	free(trimmed_input);
}
/*char *find_command_path(char *command)
{
	char	*path_env;
	char	*path_dup;
	char	*dir;
		char full_path[1024];
	int		i;
	int		j;

	path_env = getenv("PATH");
	path_dup = ft_strdup(path_env);
	dir = strtok(path_dup, ":");
	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_dup);
			return (ft_strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_dup);
	return (NULL);
}*/
char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int j;
	
	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*find_command_path(char *command)
{
	char	*path_env;
	char	**dirs;
	char	*full_path;
	int		i;
	char	temp_path[2024];

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	full_path = NULL;
	i = 0;
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
}

void	execute_external_command(char *command)
{
	char	**args;
	char	*path;
	pid_t	pid;
	int		status;

	args = ft_split(command, ' ');
	path = find_command_path(args[0]);
	if (!path)
	{
		ft_printf("🍁_(`へ´*)_🍁: %s: command not found\n", args[0]);
		free_split(args);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execv(path, args) == -1)
		{
			perror("execv");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
		perror("fork");
	free(path);
	free_split(args);
}

void	cumulate_token(char *input, t_ee *ee)
{
	static int	i = 0;
	char		copy[1024];
	int			j;

	j = 0;
	// printf("Input: %s\n", input);
	// printf("Copy: %s\n", copy);
	if (!input || input[i] == '\0')
		return ;
	while (input[i] != '\0' && input[i] != ';')
		copy[j++] = input[i++];
	copy[j] = '\0';
	// printf("Input: %c\n", input[i]);
	// printf("Copy: %s\n", copy);
	interprete_commande(copy, ee);
	// printf("%c\n", input[i]);
	if (input[i] == ';')
		i++;
	if (input[i] != '\0')
	{
		// printf("input de fin %c\n", input[i]);
		cumulate_token(input, ee);
	}
	else
	{
		i = 0;
		// printf("input apres reset %c\n", input[i]);
	}
	return ;
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	catch_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	loop(char *input, t_ee *ee)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	tok->found = 0;
	input = readline("🍀_(^o^)_🍀  > ");
	if (input == NULL || *input == '\0')
		ee->minishell_check = 1;
	if (input && *input)
	{
		add_history(input);
		if (check_string(input) == 0)
		{
			if (token_found(input, tok) == 1)
			{
				if (check_token_in_all_string(input, tok) == 1)
				{
					if (tok->token == 2)
					{
						printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;'\n");
						tok->token = 0;
					}
					else
						printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;'\n");
					free(input);
					free(tok);
					return ;
				}
				cumulate_token(input, ee);
			}
			else
				interprete_commande(input, ee);
		}
	}
	free(input);
	free(tok);
}

int	check_string(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > 32)
			return (0);
		i++;
	}
	return (1);
}

char	**copy_envp(char **envp)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (ft_strlonglen(envp) + 1));
	i = 0;
	check_variable_oldpwd(envp);
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	main(int ac, char **av, char **envp)
{
	t_ee	*ee;
	char	*input;
	int		i;

	ee = malloc(sizeof(t_ee));
	input = NULL;
	(void)ac;
	(void)av;
	init_struct(ee);
	ee->envp = copy_envp(envp);
	g_omg_le_plus_beau_du_tieks_ca_dit_koi_le_sang_trkl_la_bess_j_ai_vu_tu_connais_ici_c_est_la_debrouille = 42;
	while (ee->minishell_check == 0)
	{
		catch_signal();
		loop(input, ee);
	}
	i = 0;
	while (ee->envp[i])
	{
		free(ee->envp[i]);
		i++;
	}
	if (ee->copy_oldpwd)
		free(ee->copy_oldpwd);
	if (ee->copy_pwd)
		free(ee->copy_pwd);
	free(ee->envp);
	free(ee);
	clear_history();
	return (0);
}
