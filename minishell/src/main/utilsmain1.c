/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsmain1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:30:54 by nharraqi          #+#    #+#             */
/*   Updated: 2025/01/16 14:28:21 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig);
void loop(char *input, t_ee *ee);
void handle_environment(t_ee *ee);
char *handle_multiline_input(char *input, t_ee *ee);
int has_unmatched_quotes(const char *input);


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
//loop separee en plusieurs fonctions
void loop(char *input, t_ee *ee)
{
    t_token *tok;
    char **changed_args;

    handle_environment(ee);
    tok = malloc(sizeof(t_token));
    tok->found = 0;
    input = readline("🍀_(^o^)_🍀  > ");
    if (!input)
    {
        ee->minishell_check = 1;
        free(tok);
        return;
    }
    input = handle_multiline_input(input, ee);
    if (!input)
    {
        free(tok);
        return;
    }
    process_input(input, tok, ee);
    free(tok);
}
//loop
void handle_environment(t_ee *ee)
{
    if ((!ee->envp || !ee->envp[0]) && ee->lock_path == 0)
        you_shall_not_path();
}
//loop
char *handle_multiline_input(char *input, t_ee *ee)
{
    while (input && *input)
    {
        if (has_unmatched_quotes(input))
        {
            input = append_next_line(input, ee);
            if (!input)
                return NULL;
        }
        else
        {
            break;
        }
    }
    return input;
}
//loop
int has_unmatched_quotes(const char *input)
{
	int	i;
    int single_quotes;
    int double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '\'')
            single_quotes++;
        else if (input[i] == '"')
            double_quotes++;
		i++;
    }
    return (single_quotes % 2 != 0 || double_quotes % 2 != 0);
}
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
