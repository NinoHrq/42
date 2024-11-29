#include "../../minishell.h"

void	ft_pwd(void)
{
	char *pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("pwd");
		return ;
	}
	else
	{
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	return ;
}