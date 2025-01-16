/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsmain2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:29:11 by nharraqi          #+#    #+#             */
/*   Updated: 2025/01/16 14:34:42 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*append_next_line(char *input, t_ee *ee);
void	process_input(char *input, t_token *tok, t_ee *ee);
void	handle_syntax_error(t_token *tok);
void	execute_commands(char *input, t_token *tok, t_ee *ee);
void	you_shall_not_path(void);

//loop
char *append_next_line(char *input, t_ee *ee)
{
    char *next_line = readline("> ");
    char *temp;

    if (!next_line)
    {
        free(input);
        ee->minishell_check = 1;
        return NULL;
    }
    temp = malloc(strlen(input) + strlen(next_line) + 2);
    if (!temp)
    {
        free(input);
        free(next_line);
        return NULL;
    }
    strcpy(temp, input);
    strcat(temp, next_line);
    strcat(temp, "\n");
    free(input);
    free(next_line);
    return temp;
}
//loop
void process_input(char *input, t_token *tok, t_ee *ee)
{
    char *cleaned_input;
    char **changed_args;

    if (input && *input)
    {
        add_history(input);
        cleaned_input = handle_quotes(input, ee);
        free(input);
        input = cleaned_input;
        if (check_string(input) == 0)
        {
            if (token_found(input, tok) == 1 && check_token_in_all_string(input, tok) == 1)
            {
                handle_syntax_error(tok);
                free(input);
                return;
            }
            execute_commands(input, tok, ee);
        }
    }
    free(input);
}
//loop
void handle_syntax_error(t_token *tok)
{
    if (tok->token == 2)
        printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;\'\n");
    else if (tok->token == 3)
        printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `;;\'\n");
    tok->token = 0;
}
//loop
void execute_commands(char *input, t_token *tok, t_ee *ee)
{
    char **changed_args;

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
        free_split(changed_args);
    }
}

//loop => handle_environnement
void	you_shall_not_path(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env || *path_env == '\0')
		setenv("PATH", "/bin:/usr/bin", 1);
}