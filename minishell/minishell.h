#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"       // Bibliothèque personnelle
# include <curses.h>            // tputs, tgoto, etc.
# include <dirent.h>            // opendir, readdir, closedir, etc.
# include <errno.h>             // errno, perror, etc.
# include <readline/history.h>  // Historique des commandes
# include <readline/readline.h> // readline, add_history, etc.
# include <signal.h>            // signal, sigaction, kill, etc.
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/types.h>         // pid_t, etc.
# include <sys/wait.h>          // wait, waitpid, etc.
# include <termios.h>           // tcsetattr, tcgetattr

extern int	g_minishell_check;

typedef struct s_token
{
	int		token;
	char	*symbol;
}			t_token;

// init_c
void		init_global(void);

// ---------- BUILTINS ----------- //

// exit.c
void		ft_exit(char *input);
// pwd.c
void		ft_pwd(void);
// cd.c
void		ft_cd(char *path);
// ls.c
void		ft_ls(char *input);
// clear.c
void		ft_clear(char *input);

// ------------------------------ //

// utils.c
int			ft_strcmp(char *s1, char *s2);
void		free_split(char **array);
int			is_number(char *str);
int			check_token(char *input, t_token *token);

#endif