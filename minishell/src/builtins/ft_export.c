#include "../../minishell.h"


/*int find_env_variable(char **envp, const char *key)
{
	int i = 0;
	size_t key_len = strlen(key);

	while (envp[i]) {
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=') {
			return (i);
		}
		i++;
	}
	return (-1);
}


//a changer v
void	export_variable(t_ee *ee, const char *input, char **args)
{
	char *key = strtok(strdup(input), "=");
	int index = find_env_variable(ee->envp, key);

	if (index != -1)
	{
		free(ee->envp[index]);
		ee->envp[index] = strdup(input);
	}
	else
	{
		int len = 0;
		while (ee->envp[len]) len++;

		char **new_envp = malloc((len + 2) * sizeof(char *));
		int i = 0;
		while (i < len) {
			new_envp[i] = ee->envp[i];
			i++;
		}
		new_envp[len] = strdup(input);
		new_envp[len + 1] = NULL;

		free(ee->envp);
		ee->envp = new_envp;
	}

	free(key);
}

// Fonction principale export
void	ft_export(char *input, t_ee *ee)
{
	char **args;
	char **sorted_env;
	int i_outer;
	int i_inner;
	char *tmp;

	args = ft_split(input, ' ');
	if (input)
	{
		int len = 0;
		while (ee->envp[len])
			len++;
		sorted_env = malloc(sizeof(char *) * (len + 1));
		int i = 0;
		while (i < len)
		{
			sorted_env[i] = ee->envp[i];
			i++;
		}
		sorted_env[len] = NULL;
		i_outer = 0;
		while (i_outer < len - 1)
		{
			i_inner = i_outer + 1;
			while (i_inner < len) {
				if (ft_strcmp(sorted_env[i_outer], sorted_env[i_inner]) > 0)
				{
					tmp = sorted_env[i_outer];
					sorted_env[i_outer] = sorted_env[i_inner];
					sorted_env[i_inner] = tmp;
				}
				i_inner++;
			}
			i_outer++;
		}
		int j = 0;
		while (j < len)
		{
			printf("⚙️_(o_o;)_⚙️  %s\n", sorted_env[j]);
			j++;
		}
		free(sorted_env);
	}
	else
		export_variable(ee, input, args);
	free_split(args);
}*/

/////////////////////////////////////////////////////////////////////////////////////////////

int	ft_strcmp_dif(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

char	*parse_input_simple_export(char *input)
{
	int i = 0;
	int j = 0;
	char *copy;

	while (input[i] && input[i] <= 32)
		i++;
	int start = i;
	while (input[i] && input[i] > 32)
		i++;
	copy = malloc(sizeof(char) * (i - start + 1));
	if (!copy)
		return (NULL);
	while (start < i)
	{
		copy[j] = input[start];
		start++;
		j++;
	}
	copy[j] = '\0';
	// printf("%s\n", copy);
	return (copy);
}

void	sort_export(t_ee *ee);

void	ft_export(char *input, t_ee *ee)
{
	char **args;

	args = ft_split(input, ' ');
	if (ft_strcmp(args[0], "export=") == 0)
	{
		free_split(args);
		return ;
	}
	if (args[1] == NULL)
	{
		// printf("\n\n%s\n\n", input);
		input = parse_input_simple_export(input);
		// printf("\n\n%s\n\n", input);
		if (ft_strcmp(input, "export") == 0)
			sort_export(ee);
		free(input);
	}
	else
	{
		// dans une fonction differente pour la de norme de ses grands mort de sa mere qui tue les aliens a coup de baguette chinoise tres corporate :/// export_variable(ee,input,args);
		printf("celui qui a voulu nous faire refaire export est raciste");
	}
	free_split(args);
}

void	sort_export(t_ee *ee)
{
	char **sorted_env;
	int i_outer;
	int i_inner;
	char *tmp;

	int len = 0;
    /////////////////
	int bordel_de_merde = 0;
	if (ee->copy_oldpwd)
	{
		while (ee->envp[bordel_de_merde])
			bordel_de_merde++;
        //printf("---------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.%s\n", ee->envp[bordel_de_merde]);
        ee->envp[bordel_de_merde] = ft_strdup(ee->copy_oldpwd);
	}
	//////////////////
	while (ee->envp[len])
		len++;
	sorted_env = malloc(sizeof(char *) * (len + 1));
	int i = 0;
	while (i < len)
	{
		sorted_env[i] = ee->envp[i];
		i++;
	}
	/////////////////// une sorte de copi de l'exo sort_in_tab
	sorted_env[len] = NULL;
	i_outer = 0;
	while (i_outer < len - 1)
	{
		i_inner = i_outer + 1;
		while (i_inner < len)
		{
			if (ft_strcmp_dif(sorted_env[i_outer], sorted_env[i_inner]) > 0)
			{
				tmp = sorted_env[i_outer];
				sorted_env[i_outer] = sorted_env[i_inner];
				sorted_env[i_inner] = tmp;
			}
			i_inner++;
		}
		i_outer++;
	}
	//////////////////////////////////////////////////////////
	int j = 0;
	while (j < len)
	{
		ft_printf("⚙️_(o_o;)_⚙️  %s\n", sorted_env[j]);
		j++;
	}
	free(sorted_env);
}
