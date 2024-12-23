#include "../minishell.h"

int	ft_strlonglen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	init_struct(t_ee *ee)
{
	ee->minishell_check = 0;
	ee->change_confirmed = 0;
	ee->copy_pwd = NULL;
	ee->copy_oldpwd = NULL;
	ee->if_unset__pwd = 0;
	ee->if_unset__oldpwd = 0;
	ee->if_unset__shlvl = 0;
	ee->lock_path = 0;
	ee->copy_export_env = NULL;
	ee->path_is_not_able = 0;
	ee->save_initial_path = NULL;
}