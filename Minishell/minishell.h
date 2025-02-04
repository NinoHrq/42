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
# include <fcntl.h>

extern int	g_omg_le_plus_beau_du_tieks_ca_dit_koi_le_sang_trkl_la_bess_j_ai_vu_tu_connais_ici_c_est_la_debrouille;

typedef struct s_token
{
	int		token;
	int		found;
}			t_token;

typedef struct s_env_fonction
{
	char	*copy_pwd;
	char	*copy_oldpwd;
}			t_env;

typedef struct s_cd_fonction
{
	char	**args;
	char	*home;
}			t_cd;

typedef struct s_wc_fonction
{
	int		lines;
	int		words;
	int		chars;
	int		longest_line;
	int		current_line_length;
	int		bytes_read;
	int		flag_l;
	int		flag_w;
	int		flag_c;
	int		flag_m;
	int		flag_L;
	int		j;
}			t_wc;

typedef struct s_envp_copy
{
	int		minishell_check;
	char	**envp;
	int		change_confirmed;
	char	*copy_pwd;
	char	*copy_oldpwd;
	int		if_unset__pwd;
	int		if_unset__oldpwd;
	int		if_unset__shlvl;
	int		lock_path;
	int		path_is_not_able;
	char	**copy_export_env;
	char	*save_initial_path;
	int		check_and_validity;
	int		command_with_and;
	int		command_with_or;
	int		confirmed_command;
	int		space;
}			t_ee;

typedef struct s_redirection
{
	int command_fail;
}			t_redir;

// init_c
int			ft_strlonglen(char **s);
void		init_struct(t_ee *ee);

// ---------- BUILTINS ----------- //

// exit.c
void		ft_exit(char *input, t_ee *ee);
// pwd.c
void		ft_pwd(void);
// cd.c
char	*parse_input_cd(char *input);
void	ft_cd(char *input, t_ee *ee);
void	handle_home_directory(t_ee *ee, t_cd *cd, int result);
int		change_directory(t_ee *ee, t_cd *cd, int result);
void	free_cd_struct(t_cd *cd);
int		ft_strcmpchar(char a, char b);
void	free_and_update_envp(t_ee *ee, int i, char *copy);
int		find_pwd_index(t_ee *ee);
void	check_variable_pwd(t_ee *ee);
char	*ft_strjoin_cd(char *s1, char *s2);
// ls.c
void		ft_ls(char *input);
// clear.c
void		ft_clear(char *input);
// env.c
void		ft_env(t_ee *ee);
// unset.c
void		ft_unset(char *input, t_ee *ee);
// export.c
void		ft_export(char *input, t_ee *ee);
// echo.c
void		ft_echo(char *input);
// wc.c
void		ft_wc(char *input);

// ------------------------------ //

// utils.c
int			ft_strcmp(char *s1, char *s2);
void		free_split(char **array);
int			is_number(char *str);
int			check_token(char *input, t_token *token);
int			check_string(char *input);
char	**copy_envp(char **envp);
void		check_variable_pwd(t_ee *ee);
void		check_variable_oldpwd(char **envp);
char		*ft_strjoin_cd(char *s1, char *s2);
int			ft_strcmpchar(char a, char b);
char		*ft_strcat(char *dest, const char *src);
void		check_if_path_is_set(t_ee *ee, char **args);
int 		execute_pipeline(char *input, t_ee *ee);
char		*reconstruct_input(char **changed_args);
char		**check_dollars(char *input, t_ee *ee);
int		interprete_commande(char *input, t_ee *ee);
int	find_pipe(char *input);
int	find_or(char *input);


#endif
