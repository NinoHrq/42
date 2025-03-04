/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var_utills.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:54:32 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:54:32 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_char(t_env_expansion *exp, char c)
{
	size_t	len;
	char	*temp;

	len = strlen(exp->new_str);
	temp = malloc(len + 2);
	strcpy(temp, exp->new_str);
	temp[len] = c;
	temp[len + 1] = '\0';
	free(exp->new_str);
	exp->new_str = temp;
}

void	append_str(t_env_expansion *exp, const char *str)
{
	size_t	new_len;
	char	*temp;

	new_len = strlen(exp->new_str) + strlen(str);
	temp = malloc(new_len + 1);
	strcpy(temp, exp->new_str);
	strcat(temp, str);
	free(exp->new_str);
	exp->new_str = temp;
}

void	expand_variablee(t_env_expansion *exp, t_ee *ee)
{
	int		j;
	char	*var_name;
	char	*value;

	j = exp->i;
	while (exp->input[j] && (isalnum(exp->input[j]) || exp->input[j] == '_'))
		j++;
	var_name = strndup(&exp->input[exp->i], j - exp->i);
	value = get_env_valueee(var_name, ee);
	free(var_name);
	append_str(exp, value);
	free(value);
	exp->i = j;
}

void	set_value_dollars(char **input, t_ee *ee)
{
	t_env_expansion	exp;

	exp.new_str = malloc(1);
	if (!exp.new_str)
		return ;
	exp.input = *input;
	exp.i = 0;
	exp.new_str[0] = '\0';
	while (exp.input[exp.i])
	{
		if (exp.input[exp.i] == '$' && exp.input[exp.i + 1]
			&& (isalnum(exp.input[exp.i + 1]) || exp.input[exp.i + 1] == '_'))
		{
			exp.i++;
			expand_variablee(&exp, ee);
		}
		else
		{
			append_char(&exp, exp.input[exp.i]);
			exp.i++;
		}
	}
	free(*input);
	*input = exp.new_str;
}
//////////////////////////////////////////
/*void set_value_dollars(char **input, t_ee *ee)
{
	char *str = *input;
	char *new_str = malloc(1);
	new_str[0] = '\0';
	int i = 0, j;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (isalnum(str[i + 1]) || str[i
				+ 1] == '_'))
		{
			i++;
			j = i;
			while (str[j] && (isalnum(str[j]) || str[j] == '_'))
				j++;
			char *var_name = strndup(&str[i], j - i);
			char *value = get_env_valueee(var_name, ee);
			free(var_name);
			char *temp = malloc(strlen(new_str) + strlen(value) + 1);
			strcpy(temp, new_str);
			strcat(temp, value);
			free(new_str);
			free(value);
			new_str = temp;
			i = j;
		}
		else
		{
			char *temp = malloc(strlen(new_str) + 2);
			strcpy(temp, new_str);
			temp[strlen(new_str)] = str[i];
			temp[strlen(new_str) + 1] = '\0';
			free(new_str);
			new_str = temp;
			i++;
		}
	}
	free(*input);
	*input = new_str;
}*/