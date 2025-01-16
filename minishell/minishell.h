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
	//      V signal exit
	int		minishell_check;
	//      V copy l'environnement
	char	**envp;
	//      V confirme dans cd le changement de directory
	int		change_confirmed;
	//      V copy dans cd le pwd apres le changement de directory
	char	*copy_pwd;
	//      V copy dans cd le pwd avant le changement de directory
	char	*copy_oldpwd;
	//		V condition pour verifier si pwd a ete unset (pour ne plus l'afficher)
	int		if_unset__pwd;
	//		V condition pour verifier si oldpwd a ete unset (pour ne plus l'afficher)
	int		if_unset__oldpwd;
	//		V condition pour verifier si shlvl a ete unset (pour ne plus l'afficher)
	int		if_unset__shlvl;
	//		V (si env -i) lock permettant de ne pas setenv PATH a chaque nouvel input s'il a deja ete unset
	int		lock_path;
	//		V sert a bloquer les commande si le PATH est retire
	int		path_is_not_able;
	//		V etre le tableau de char * de la commande export
	char	**copy_export_env;
	//		V enregistre le path initiale si existant
	char	*save_initial_path;
}			t_ee;

// init_c
int			ft_strlonglen(char **s);
void		init_struct(t_ee *ee);

// ---------- BUILTINS ----------- //

// exit.c
void		ft_exit(char *input, t_ee *ee);
// pwd.c
void		ft_pwd(void);
// cd.c
void		ft_cd(char *input, t_ee *ee);
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
char		**copy_envp(char **envp);
void		check_variable_pwd(t_ee *ee);
void		check_variable_oldpwd(char **envp);
char		*ft_strjoin_cd(char *s1, char *s2);
int			ft_strcmpchar(char a, char b);
char		*ft_strcat(char *dest, const char *src);
void		check_if_path_is_set(t_ee *ee, char **args);
void 		execute_pipeline(char *input, t_ee *ee);
char		*reconstruct_input(char **changed_args);
char		**check_dollars(char *input, t_ee *ee);


#endif
