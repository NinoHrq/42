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
	int single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == ';' && input[i + 1] == ';')
			break ;
		if (input[i] == 39)
			single_quote++;
		if (input[i] == 34)
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (0);
	i = 0;
	while (input[i])
	{
		if (input[i] == ';')
		{
			if (input[i + 1] == '\0')
				return (0);
			if (input[i + 1] == ';')
			{
				tok->token = 3;
				return (1);
			}
			i++;
			while (input[i] && input[i] <= 32)
				i++;
			if (input[i] == ';')
			{
				tok->token = 2;
				return (1);
			}
			if (input[i] == '\0')
				return (0);
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

void	execute_external_command(char *command, t_ee *ee);

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
		ft_cd(input, ee);
	}
	else if (ft_strcmp(trimmed_input, "env") == 0)
	{
		if (ee->path_is_not_able == 0)
			ft_env(ee);
		else
			ft_printf("🌳(´•︵•`)🌳: env: No such file or directory\n");
	}
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
			execute_external_command(input, ee);
	}
	free(token);
	free(trimmed_input);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

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

/*int is_command_in_envp(char *command, t_ee *ee)
{
    int i = 0;
    char *env_value;
    char *env_command;

    while (ee->envp[i] != NULL)
    {
        if ((env_value = ft_strchr(ee->envp[i], '=')) != NULL)
        {
            env_command = env_value + 1;
            if (ft_strcmp(command, env_command) == 0)
                return 1;
        }
        i++;
    }
    return 0;
}*/


void	execute_external_command(char *command, t_ee *ee)
{
	char	**args;
	char	*path;
	pid_t	pid;
	int		status;

	(void)ee;
	args = ft_split(command, ' ');
	path = find_command_path(args[0]);
	if (!path)
	{
		/*if (is_command_in_envp(command, ee) == 1)
		{
			printf("%s\n", command);
			free_split(args);
			return ;
		}
		else
		{*/
			ft_printf("🍁_(`へ´*)_🍁: %s: command not found\n", args[0]);
			free_split(args);
			return ;
		//}
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


int cumulate_token(char *input, t_ee *ee)
{
    int i = 0;
    char copy[1024];
    int j = 0;
    char **changed_args;

	if (!input || input[i] == '\0')
		return (1);
    while (input[i] != '\0')
    {
        while (input[i] != '\0' && input[i] != ';')
            copy[j++] = input[i++];
        copy[j] = '\0';
        changed_args = check_dollars(copy, ee);
        if (!changed_args)
            return 1;
        char *reconstructed_input = reconstruct_input(changed_args);
        if (ft_strchr(reconstructed_input, '|'))
            execute_pipeline(reconstructed_input, ee);
        else
                interprete_commande(reconstructed_input, ee);
        free_split(changed_args);
        free(reconstructed_input);
        if (input[i] == ';')
            i++;
        j = 0;
    }
    return 0;
}


/*int	cumulate_token(char *input, t_ee *ee)
{
	static int	i = 0;
	char		copy[1024];
	int			j;

	j = 0;
	if (!input || input[i] == '\0')
		return (1);
	while (input[i] != '\0' && input[i] != ';')
		copy[j++] = input[i++];
	copy[j] = '\0';
	if (ft_strchr(copy, '|')) 
        execute_pipeline(copy, ee);
	else
		interprete_commande(copy, ee);
	if (input[i] == ';')
		i++;
	if (input[i] != '\0')
		cumulate_token(input, ee);
	else
		i = 0;
	return (0);
}*/

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

void	you_shall_not_path(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env || *path_env == '\0')
		setenv("PATH", "/bin:/usr/bin", 1);
}

char	**parse_dollars(char **args, t_ee *ee)
{
	char	*copy;
	char	**changed_args;
	char	*after_equal;
	char	*before_equal;
	int		lock;
	int i, j, k, x, y, m;
	
	changed_args = malloc(sizeof(char *) * (ft_strlonglen(args) + 1));
	if (!changed_args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		lock = 0;
		if (args[i][0] == '$')
		{
			copy = malloc(sizeof(char) * ft_strlen(args[i]));
			if (!copy)
				return (NULL);
			j = 1;
			k = 0;
			while (args[i][j])
				copy[k++] = args[i][j++];
			copy[k] = '\0';
			x = 0;
			while (ee->envp[x])
			{
				y = 0;
				if (ft_strncmp(ee->envp[x], copy, ft_strlen(copy)) == 0
					&& ee->envp[x][ft_strlen(copy)] == '=')
				{
					y = ft_strlen(copy) + 1;
					after_equal = ft_strdup(ee->envp[x] + y);
					if (!after_equal)
						return (NULL);
					changed_args[i] = after_equal;
					lock = 1;
					break ;
				}
				x++;
			}
			if (!lock)
				changed_args[i] = ft_strdup(args[i]);
			free(copy);
		}
		else
		{
			j = 0;
			while (args[i][j] && args[i][j] != '$')
				j++;
			if (args[i][j] == '$')
			{
				m = j;
				before_equal = malloc(sizeof(char) * (m + 1));
				if (!before_equal)
					return (NULL);
				k = 0;
				while (k < m)
				{
					before_equal[k] = args[i][k];
					k++;
				}
				before_equal[m] = '\0';
				changed_args[i] = before_equal;
				lock = 1;
			}
			if (!lock)
				changed_args[i] = ft_strdup(args[i]);
		}
		i++;
	}
	changed_args[i] = NULL;
	return (changed_args);
}

char	**check_dollars(char *input, t_ee *ee)
{
	char	**args;
	char	**changed_args;

	args = ft_split(input, ' ');
	if (!args)
		return (NULL);
	changed_args = parse_dollars(args, ee);
	if (!changed_args)
		return (NULL);
	free_split(args);
	return (changed_args);
}

char	*reconstruct_input(char **changed_args)
{
	int		i;
	size_t	total_len;
	char	*new_input;
	char	*current_pos;
	size_t	len;

	i = 0;
	total_len = 0;
	while (changed_args[i])
	{
		total_len += ft_strlen(changed_args[i]) + 1;
		i++;
	}
	new_input = malloc(sizeof(char) * total_len);
	if (!new_input)
		return (NULL);
	current_pos = new_input;
	i = 0;
	while (changed_args[i])
	{
		len = ft_strlen(changed_args[i]);
		ft_memcpy(current_pos, changed_args[i], len);
		current_pos += len;
		if (changed_args[i + 1])
			*current_pos++ = ' ';
		i++;
	}
	*current_pos = '\0';
	return (new_input);
}



// Pour les pipe il faut d abord detecter si y'en a si oui il faut split avec '|' comme separateur
// pour diviser l'input en deux puis exec la commande qui contient le pipe 

void execute_pipeline(char *input, t_ee *ee) 
{
    char **commands;
    int pipe_fd[2];
    int prev_fd = -1;
    pid_t pid;
    int i = 0;

    commands = ft_split(input, '|');
    while (commands[i])
	{
        if (pipe(pipe_fd) == -1)
		{
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if (pid == -1)
		{
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
		{
            if (prev_fd != -1) 
			{
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (commands[i + 1])
			{
                dup2(pipe_fd[1], STDOUT_FILENO);
            }
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            interprete_commande(commands[i], ee);
            exit(EXIT_FAILURE);
        }
		else
		{
            close(pipe_fd[1]);
            if (prev_fd != -1)
			{
                close(prev_fd);
            }
            prev_fd = pipe_fd[0];
        }
        i++;
    }
    if (prev_fd != -1) 
        close(prev_fd);
    while (wait(NULL) > 0);
    free_split(commands);
}





char *find_env_var(const char *var_name, t_ee *ee)
{
    int i = 0;
    int name_len = ft_strlen(var_name);

    while (ee->envp && ee->envp[i])
	{
        if (ft_strncmp(ee->envp[i], var_name, name_len) == 0 && ee->envp[i][name_len] == '=')
            return ft_strdup(&ee->envp[i][name_len + 1]);
        i++;
    }
    return NULL;
}


char *expand_variable(char *input, t_ee *ee)
{
    char var_name[256];
    int i = 1;
    int j = 0;
    char *value;

    while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
	{
        if (j < 255)
            var_name[j++] = input[i++];
    }
    var_name[j] = '\0';

    value = find_env_var(var_name, ee);
    if (value)
        return value;
    return ft_strdup("");
}




char *handle_quotes(char *input, t_ee *ee)
{
    char *result = malloc(1024);
    int size = 1024;
    int i = 0, j = 0;
    char quote = '\0';
    char *expanded;
	int expanded_len;

    if (!result)
        return NULL;
    while (input[i])
	{
        if ((input[i] == '\'' || input[i] == '"') && quote == '\0') {
            quote = input[i++];
        }
		else if (input[i] == quote)
		{
            quote = '\0';
            i++;
        } 
		else
		{
            if (quote == '"' && input[i] == '$')
			{
                expanded = expand_variable(&input[i], ee);
                if (expanded)
				{
                    expanded_len = ft_strlen(expanded);
                    if (j + expanded_len >= size)
					{
                        size *= 2;
                        result = realloc(result, size);
                        if (!result) {
                            free(expanded);
                            return NULL;
                        }
                    }
                    strcpy(&result[j], expanded);
                    j += expanded_len;
                    free(expanded);
                    i++;
                    while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
                        i++;
                    continue;
                }
            }
            if (j + 1 >= size)
			{
                size *= 2;
                result = realloc(result, size);
                if (!result)
                    return NULL;
            }
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';
    return result;
}





void loop(char *input, t_ee *ee)
{
    t_token *tok;
    char **changed_args;
	char *cleaned_input;

	//// Pour les quotes V
    int single_quotes = 0;
    int double_quotes = 0;
    int i;
	char *temp;
	char *next_line;
	////

    changed_args = NULL;
    if ((!ee->envp || !ee->envp[0]) && ee->lock_path == 0)
        you_shall_not_path();
    tok = malloc(sizeof(t_token));
    tok->found = 0;
    input = readline("🍀_(^o^)_🍀  > ");
    if (input == NULL)
	{
        ee->minishell_check = 1;
	}
	while (input && *input)
    {
        single_quotes = 0;
        double_quotes = 0;
        for (i = 0; input[i] != '\0'; i++)
        {
            if (input[i] == '\'')
                single_quotes++;
            else if (input[i] == '"')
                double_quotes++;
        }
        if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
        {
            next_line = readline("> ");
            if (next_line == NULL)
            {
                free(input);
                ee->minishell_check = 1;
                return;
            }
            temp = malloc(strlen(input) + strlen(next_line) + 1);
            if (!temp)
            {
                free(input);
                free(next_line);
                return;
            }
            strcpy(temp, input);
            strcat(temp, next_line);
			strcat(temp, "\n");

            free(input);
            free(next_line);
            input = temp;
        }
        else
		{
			break ;
		}
    }
    if (input && *input)
	{
        add_history(input);
        cleaned_input = handle_quotes(input, ee);
        free(input);
        input = cleaned_input;
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
					else if (tok->token == 3) 
                        printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;'\n");
                    free(input);
                    free(tok);
                    return;
                }
            }
            if (ft_strchr(input, '|') && cumulate_token(input, ee) == 1)
            	execute_pipeline(input, ee);
			else if (!ft_strchr(input, '|') && cumulate_token(input, ee) == 1 ||&& || ||) 
			{
                changed_args = check_dollars(input, ee);
                if (!changed_args)
                    return;
                free(input);
                input = reconstruct_input(changed_args);
                interprete_commande(input, ee);
            }
        }
    }
    free_split(changed_args);
    free(input);
    free(tok);
}




/*void loop(char *input, t_ee *ee)
{
    t_token *tok;
    char **changed_args;

    changed_args = NULL;
    if ((!ee->envp || !ee->envp[0]) && ee->lock_path == 0)
        you_shall_not_path();
    tok = malloc(sizeof(t_token));
    tok->found = 0;
    input = readline("🍀_(^o^)_🍀  > ");
    if (input == NULL)
        ee->minishell_check = 1;
    if (input && *input) 
	{
        add_history(input);
        if (check_string(input) == 0) 
		{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (token_found(input, tok) == 1)
			{
				if (check_token_in_all_string(input, tok) == 1)
				{
					if (tok->token == 2)
					{
						printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;'\n");
						tok->token = 0;
					}
					else if (tok->token == 3)
						printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;'\n");
					free(input);
					free(tok);
					return ;
				}
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (ft_strchr(input, '|') && cumulate_token(input, ee) == 1) 
			{
                execute_pipeline(input, ee);
            }
			else if (!ft_strchr(input, '|') && cumulate_token(input, ee) == 1) 
			{
                changed_args = check_dollars(input, ee);
                if (!changed_args)
                    return;
                free(input);
                input = reconstruct_input(changed_args);
                interprete_commande(input, ee);
            }
        }
    }
    free_split(changed_args);
    free(input);
    free(tok);
}*/




/// 			ANCIENNE LOOP



/*void	loop(char *input, t_ee *ee)
{
	t_token	*tok;
	char	**changed_args;

	changed_args = NULL;
	if ((!ee->envp || !ee->envp[0]) && ee->lock_path == 0)
		you_shall_not_path();
	tok = malloc(sizeof(t_token));
	tok->found = 0;
	input = readline("🍀_(^o^)_🍀  > ");
	if (input == NULL)
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
					else if (tok->token == 3)
						printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;'\n");
					free(input);
					free(tok);
					return ;
				}
				changed_args = check_dollars(input, ee);
				if (!changed_args)
					return ;
				free(input);
				input = reconstruct_input(changed_args);
				cumulate_token(input, ee);
			}
			else
			{
				changed_args = check_dollars(input, ee);
				if (!changed_args)
					return ;
				free(input);
				input = reconstruct_input(changed_args);
				interprete_commande(input, ee);
			}
		}
	}
	free_split(changed_args);
	free(input);
	free(tok);
}*/

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

char	*save_initial_path(t_ee *ee)
{
	int i = 0;
	char *tmp;

	tmp = NULL;
	while (ee->envp[i])
	{
		if (ee->envp[i][0] == 'P' && ee->envp[i][1] == 'A' && ee->envp[i][2] == 'T' && ee->envp[i][3] == 'H' && ee->envp[i][4] == '=')
		{
			tmp = ft_strdup(ee->envp[i]);
			break ;
		}
		i++;
	}
	return (tmp);
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
	ee->save_initial_path = save_initial_path(ee);
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
	if (ee->envp)
		free(ee->envp);
	if (ee->copy_export_env)
		free_split(ee->copy_export_env);
	if (ee->save_initial_path)
		free(ee->save_initial_path);
	free(ee);
	clear_history();
	return (0);
}