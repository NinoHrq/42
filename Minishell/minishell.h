/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:39:37 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:45:55 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_LEN 2048

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

extern int			g_status;

typedef struct s_token
{
	int				token;
	int				found;
	char			*trimmed_input;
}					t_token;

typedef struct s_env_fonction
{
	char			*copy_pwd;
	char			*copy_oldpwd;
}					t_env;

typedef struct s_cd_fonction
{
	int				result;
	char			**args;
	char			*home;
}					t_cd;

typedef struct s_quote
{
	int				single_quotes;
	int				double_quotes;
	char			*temp;
	char			*next_line;
}					t_quote;

typedef struct s_tableautt
{
	int				i;
	int				j;
	int				k;
	int				m;
	int				in_quotes;
}					t_tableautt;

typedef struct s_loop
{
	char			**changed_args;
	char			*cleaned_input;
	char			*input;
	pid_t			pid;
}					t_loop;

typedef struct s_pipe
{
	int				prev_fd;
	int				i;
	char			**commands;
	pid_t			pid;
}					t_pipe;

typedef struct s_pipeline
{
	char			**commands;
	int				pipe_fd[2];
	int				prev_fd;
	pid_t			pid;
	int				i;
	char			*final_command;
	int				heredoc_fd;
	int				input_fd;
	int				output_fd;
	int				breakk;
}					t_pipeline;

typedef struct s_reconstruct
{
	int				i;
	size_t			total_len;
	char			*new_input;
	char			*current_pos;
	size_t			len;
}					t_reconstruct;

typedef struct s_pipeline_parser
{
	int				i;
	int				j;
	int				extra_spaces;
	char			*tmp;
}					t_pipeline_parser;

typedef struct s_parentheses_remover
{
	int				i;
	int				j;
	int				level;
	char			*tmp;
}					t_parentheses_remover;

typedef struct s_dollar_parser
{
	char			*copy;
	char			**changed_args;
	char			*after_equal;
	char			*before_equal;
	int				lock;
	int				i;
	int				j;
	int				k;
	int				x;
	int				y;
	int				m;
}					t_dollar_parser;

typedef struct s_open
{
	char			*tmp_dir;
	char			*idxstr;
	char			*final_filename;
	int				i;
	int				fd;
}					t_open;

typedef struct s_varex
{
	char			tmp[5000];
	int				i;
	int				j;
	int				k;
}					t_varex;

typedef struct s_quote_handler
{
	char			*result;
	int				size;
	int				i;
	int				j;
	char			quote;
	char			*expanded;
	int				expanded_len;
}					t_quote_handler;

typedef struct s_separator_handler
{
	int				i;
	int				j;
	int				count_how_many_sep;
	char			*good_sep;
}					t_separator_handler;

typedef struct s_redir
{
	int				command_fail;
}					t_redir;

typedef struct s_quote_normalizer
{
	int				i;
	int				j;
	int				k;
	char			quote_type;
	char			result[MAX_LEN];
}					t_quote_normalizer;

typedef struct s_redir_handler
{
	char			**split_in;
	char			**split_execv;
	char			*tmp;
	int				last_name;
	int				file;
	pid_t			pid;
	char			*path;
	char			*input_execv;
	char			*heredoc_tmpfile;
	int				heredoc_fd;
	char			*delimiter;
	int				heredoc_count;
	char			*tmpfilenames[10];
	int				fd;
	int				status;
	char			buffer[1024];
	int				i;
	t_redir			*re;
}					t_redir_handler;

typedef struct s_redir_simple
{
	char			*input_execv;
	char			*if_need_sep;
	char			**split_in;
	char			**split_execv;
	char			*path;
	char			*heredoc_tmpfile;
	char			*tmpfilenames[10];
	char			*delimiter;
	int				last_name;
	int				file;
	int				heredoc_fd;
	int				heredoc_count;
	int				fd;
	int				status;
	int				help;
	pid_t			pid;
}					t_redir_simple;

typedef struct s_parenthese
{
	char			*clean_input;
	char			*command_before_or;
	char			*command_after_or;
}					t_parenthese;

typedef struct s_unset_data
{
	int				i;
	int				j;
	int				k;
	int				skip;
	int				len;
	char			**args;
	char			**new_envp;
}					t_unset_data;

typedef struct s_ls
{
	char			**args;
	char			*path;
	DIR				*dir;
	int				file_found;
	struct dirent	*entry;
}					t_ls;

typedef struct s_env
{
	char			**envp;
	char			**copy_export_env;
	int				len_envp;
	int				len_export;
}					t_envv;

typedef struct s_ewa
{
	char			**copy_envp;
	char			**copy_export;
	int				len_envp;
	int				len_export;
	int				count_equal;
	int				count_args_without_equal;
}					t_ewa;

typedef struct s_rdp
{
	int				i;
	int				j;
	int				k;
	int				len_env;
	int				*to_keep;
	char			**result;
	size_t			name_i_len;
	size_t			name_j_len;
	char			*name_i;
	char			*name_j;
	int				new_len;
}					t_rdp;

typedef struct s_env_expansion
{
	char			*new_str;
	char			*input;
	int				i;
}					t_env_expansion;

typedef struct s_envp_copy
{
	int				error_exit;
	int				reset_sigint;
	int				code_exit;
	int				minishell_check;
	int				change_confirmed;
	int				if_unset__pwd;
	int				if_unset__oldpwd;
	int				if_unset__shlvl;
	int				lock_path;
	int				path_is_not_able;
	int				check_and_validity;
	int				command_with_and;
	int				command_with_or;
	int				confirmed_command;
	int				signal;
	int				save_result;
	int				block_home;
	char			**envp;
	char			*copy_pwd;
	char			*copy_oldpwd;
	char			**copy_export_env;
	char			*save_initial_path;
	char			*copy_home;
}					t_ee;

// ---------- BUILTINS ----------- //

void				ft_exit(char *input, t_ee *ee);
void				ft_pwd(void);
void				ft_cd(char *input, t_ee *ee);
void				ft_clear(char *input);
void				ft_env(t_ee *ee);
void				ft_unset(char *input, t_ee *ee);
void				ft_export(char *input, t_ee *ee);
void				ft_echo(char *input, t_ee *ee);

// ------------------------------ //

int					verif_what_after_redirection(char *input, t_ee *ee);
int					parse_tmp(char *tmp, t_loop *loop, t_ee *ee);
void				process_quotes(char *arg, t_quote_normalizer *q);
int					check_quotes(char *arg, t_quote_normalizer *q);
void				init_normalizer(t_quote_normalizer *q);
char				**parse_dollarsss(char **args, t_ee *ee);
void				remoov_quote__(char **args);
int					f_q(char *input);
void				verif_what_after_redirection_utils(char *input, int *i);
int					found_single__(char *input);
int					found_single_or_double__(char *input);
void				for_quote_at_start(char ***args);
char				**ft_splittt(const char *st, char sep);
int					ft_strcmp(char *s1, char *s2);
int					is_number(char *str);
int					ft_strlonglen(char **s);
void				init_struct(t_ee *ee);
void				free_split(char **array);
char				*skip_isspace_for_fonctions(char *input, t_token *token);
char				*ft_strcat(char *dest, const char *src);
int					skip_whitespace(const char *tmp);
int					skip_whitespacee(const char *tmp, int i);
int					check_token(char *input, t_token *token);
int					check_after_token(char *input, int i);
char				*find_command_path(char *command);
void				you_shall_not_path(void);
int					calcul_check_path(char **check_path);
void				check_path_in_or_with_pipe(char *input, t_ee *ee);
char				*save_initial_path(t_ee *ee);
char				**copy_envp(char **envp);
void				init_struct_loop(t_loop *loop);
void				loop(char *tmp, t_ee *ee);
char				*parse_env_value(char *value);
int					found_only_one_redirection(char *input);
int					i_want_to_sing_a_song_hiihi(t_redir_handler *hr);
char				*cut_for_no_leaks_at_the_end(char *input);
int					check_the_end(char *input);
char				*get_env_valueee(char *key, t_ee *ee);
int					do_you_find_or_what(char *input);
int					find_parenthesis(char *input);
void				open_input_file(t_redir_simple *hr, char *filename);
char				**parse_dollars(char **args, t_ee *ee);
char				*reconstruct_input(char **changed_args);
char				*parse_input_pipeline(char *input);
char				**check_dollars(char *input, t_ee *ee);
char				*remove_parentheses(char *input);
char				*parse_exev_input(char *tmp_in);
int					find_pipe(char *input);
int					process_multiple_heredocs(t_redir_simple *hr, t_ee *ee,
						char *buffer);
int					process_single_heredoc(t_redir_simple *hr, t_ee *ee,
						char *buffer);
void				ft_freetableautt(char **tab, int len);
int					count_wordstt(const char *str, char sep);
char				*parse_final_command(char *input);
void				tableau_picasso(t_tableautt *tt);
int					execute_pipeline(char *input, t_ee *ee);
int					execute_pipeline_heredoc(char *input, t_ee *ee);
int					find_redirection(char *input);
int					find_type_of_redirection(char *tmp_in);
char				*unstick_to_re_stick(char *input);
int					open_available(char **tmpfilename);
void				handle_herdoc_sigint(int status);
int					write_to_tmpfile(int fd, char *limit, t_ee *ee);
void				handle_redirection(char *input, t_ee *ee);
char				*foud_delimiter(char **split_in);
int					check_after_or(char *input);
int					find_or(char *input);
void				if_path_is_incorrect(char **args, t_ee *ee);
char				*copy_before_or(char *src);
void				error_access(char *command);
char				*copy_after_or(char *src);
char				*copy_pasta(char *l, int *i, t_ee *ee);
void				copy_until_parenthesis(char *l, int *i, char *copy, int *j);
int					process_segment(char *segment, t_ee *ee);
bool				process_token(char *input, int *i, t_ee *ee, bool success);
void				free_after_or(char *co, char *com, t_ee *ee);
char				*parse_command_after(char *command_after_or);
void				if_confirmed_command_equal_to_zero(char *c, t_ee *ee);
void				check_valid_after(char *command_after_or, t_ee *ee);
void				after_find_or(char *input, t_ee *ee);
int					handle_or_and_redirection(char *input, t_ee *ee);
void				init_value_token(t_token *token, char *input);
void				at_the_end(t_token *token, t_ee *ee);
void				if_echo(char *input, t_ee *ee);
void				if_exit(t_token *token, char *input, t_ee *ee);
void				if_pwd(t_ee *ee);
void				if_cd(char *input, t_ee *ee);
void				if_env(t_ee *ee);
void				if_unset(char *input, t_ee *ee);
void				if_export(char *input, t_ee *ee);
void				if_dq(t_ee *ee, t_token *token);
void				if_else(t_token *token, char *input, t_ee *ee);
int					cumulate_token(char *input, t_ee *ee);
int					interprete_commande(char *input, t_ee *ee);
void				execute_external_command(char *command, t_ee *ee);
void				init_quote_struct(t_quote *qt);
char				*append_next_line(char *input, t_ee *ee);
char				*handle_unclosed_quotes(char *input, t_ee *ee);
int					check_syntax_at_start(const char *tmp, t_ee *ee);
int					check_syntax_in_body(const char *tmp, t_ee *ee);
int					check_syntax_error(const char *tmp, t_ee *ee);
int					check_unexpected_semicolon(char *tmp, t_ee *ee);
int					find_trap(char *input);
void				cleanup_loop(t_loop *loop);
int					check_tmp_not_null(char *tmp, t_ee *ee);
void				for_norminette(t_ee *ee);
void				its_just_a_parenthese(char *input, t_ee *ee);
char				*find_env_var(const char *var_name, t_ee *ee);
char				*expand_variable(char *input, t_ee *ee);
char				*handle_quotes(char *input, t_ee *ee);
void				handle_sigint(int sig);
void				catch_signal(t_ee *ee);
void				check_variable_pwd(t_ee *ee);
char				*ft_strjoin_cd(char *s1, char *s2);
int					ft_strcmpchar(char a, char b);
void				check_if_path_is_set(t_ee *ee, char **args);
char				*ft_strcat_export(char *s1, char *s2);
void				sort_export(t_ee *ee, char **sorted);
char				**remove_duplicates_with_priority(char **env);
void				export_with_args(t_ee *ee, char **args);
char				**copi_colle(t_ee *ee);
void				handle_export_without_equals(char **a, char ***c, int *l);
void				handle_env_with_equals(char **a, char ***c, int *l);
int					ft_found_equal(char c);
char				*ft_strndup(const char *s, size_t n);
void				check_variable_oldpwd(char **envp);
int					find_pipe(char *input);
void				check_signal(char *command, t_ee *ee);
void				path_checker(char *input, t_ee *ee);
void				path_confirm(char *input);
void				init_pipe_struct(t_pipe *pipe);
char				*handle_redi_with_pipe(char *t, t_ee *e, t_pipeline *p);
void				close_fds_and_update(t_pipeline *p);
void				close_fds(t_pipeline *p);
void				pid_sup_to_zero_pipe_redi(t_pipeline *p);
int					handle_error(const char *msg, t_pipeline *p, char *input);
void				init_remover(t_parentheses_remover *r, char *input);
char				*parse_input_exit(char *input, t_token *exit);
char				*ft_strncpy(char *dest, const char *src, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					count_extra_spaces(char *input);
char				*parse_redirection_at_start(char *input);
char				*cut_for_no_leaks_at_the_end(char *input);
int					count_first_or_last(char *input, char c);
char				*extract_var_name(char *arg);
char				*get_env_value(char *var_name, t_ee *ee);
char				*handle_dollar_variable(char *arg, t_ee *ee);
char				*extract_text_before_dollar(char *arg);
int					count_extra_spaces_pipeline(char *input);
void				norminette_tricks(void);
void				init_quote_handler(t_quote_handler *qh);
int					handle_expansion(t_quote_handler *q, char *i, t_ee *e);
void				expand_buffer_if_needed(t_quote_handler *qh);
void				all_is__freed(t_ee *ee);
int					count_separators(char *input);
char				*allocate_good_sep(char *input, int extra_spaces);
void				fill_good_sep(t_separator_handler *sh, char *input);
int					does_exit_final_filename(t_open openn);
void				init_redir_handler(t_redir_handler *handler, char *input);
void				redi_pipe_free(t_redir_handler *hr);
void				redi_last_free(t_redir_handler *hr);
void				init_p_fd(t_pipeline *p);
void				init_varex(t_varex *v);
void				gandalf_le_grand_prince(t_redir_handler *hr, char c);
int					norminette_backflip(char *fi, t_redir_handler *hr);
int					find_redirection_and_pipe(char *input);
void				free_if_simple_redir_fail(t_redir_simple *hr);
t_redir_simple		*init_redirr_handler(char *input);
void				handle_parent_process(t_redir_simple *hr, t_ee *ee);
void				handle_child_simple_process(t_redir_simple *hr, t_ee *ee);
int					fork_and_execute(t_redir_simple *hr, t_ee *ee);
void				open_output_file(t_redir_simple *hr, char *o, int f);
void				redirect_output(t_redir_simple *hr);
void				free_at_last(t_redir_simple *hr);
void				free_if_pid_is_n(t_redir_simple *hr);
int					init_heredoc(t_redir_simple *hr);
int					handle_heredoc(t_redir_simple *hr, t_ee *ee);
void				handle_otpt_redirection(t_redir_simple *hr);
int					finalize_heredoc(t_redir_simple *hr);
int					process_heredoc_entries(t_redir_simple *hr, t_ee *ee);
int					read_and_write_heredoc(t_redir_simple *hr, char *buffer);
char				*complete_tmp(char *src, int i);
int					check_for_no_double(char *input, t_ee *ee);
void				home_is_cooked(t_cd *cd);
char				*parse_input_cd(char *input);
void				careful_fire_burns(t_ee *ee, t_cd *cd);
void				am_i_cooked(char *input, t_cd *cd, t_ee *ee);
void				no_inspi_jutsu(t_cd *cd, t_ee *ee);
void				norminette_invocation(t_cd *cd);
int					find_pwd_index(t_ee *ee);
void				update_pwd_variable(t_ee *ee, int index);
int					check_simple_exit(char *input);
void				handle_exit_no_args(char **args, t_ee *ee, t_token *exit);
void				handle_exit_syntax_error(void);
void				handle_exit_numeric_error(char **a, t_ee *ee, t_token *e);
void				bilbon_the_saquet(char **args, char *command, t_ee *ee);
int					find_oldpwd_index(char **envp);
void				remove_oldpwd_from_env(char **envp, int index);
void				norminette_heelflip(t_ee *ee);
void				norminette_hardflip(t_unset_data *data, t_ee *ee);
void				norminette_pop_shove_it(t_ee *ee);
char				*save_initial_home(t_ee *ee);
void				check_if_home_is_set(t_ee *ee, char **args);
void				init_ls(t_ls *ls, char *input);
char				*parse_input_ls(char *input);
void				clean_up_ls(t_ls *ls);
void				assign_rdp_name(t_rdp *rdp, char **env);
char				*parse_input_simple_export(char *input);
int					ft_strcmp_dif(char *s1, char *s2);
int					ft_check_equal(const char *s);
void				check_if_home_is_not_modified(t_ee *ee, char **args);
void				check_if_path_is_not_modified(t_ee *ee, char **args);
void				handle_sigquit(int sig);
void				process_exit(char **args, t_ee *ee, t_token *exit);
char				*ft_strstr(char *to_find, char *str);
int					check_atoi_overflow(char *str);
void				print_invalid_identifier(const char *arg);
size_t				get_key_length(const char *arg);
void				initialize_ewa(t_ewa *ewa);
void				initialize_rdp(t_rdp *rdp);
void				allocate_result(t_rdp *rdp);
void				calculate_lengths(t_envv *env, t_ee *ee);
char				**allocate_memory(t_envv *env);
void				allocate_and_copy_export(t_ewa *ewa, t_ee *ee);
void				allocate_and_copy_envp(t_ewa *ewa, t_ee *ee);
void				count_arguments(t_ewa *ewa, char **args);
void				count_env_length(t_rdp *rdp, char **env);
void				allocate_to_keep(t_rdp *rdp);
void				do_what_dq_do(t_ee *ee);
void				normalize_quotes(char **args);
bool				norminette_udertaker(bool success, t_ee *ee);
void				copy_before_or_utils(char *src, int *i);
size_t				ft_strcspn(const char *str, const char *reject);
void				remove_duplicates(t_rdp *rdp, char **env);
char				**copy_filtered_env(t_rdp *rdp, char **env);
void				print_and_free_sorted_env(char **sorted_env, int len);
void				sort_sorted_env(char **sorted_env, int len);
void				add_oldpwd(t_ee *ee, char **sorted_env, int *len);
void				bilbon_saquet(t_ee *ee, char **args);
void				norminette_backstab(t_ee *ee, char **args);
void				process_simple_export(char *input, t_ee *ee);
int					found_single_or_double_quote(char *input);
int					printf_expand_var(char *input, t_ee *ee);
void				set_value_dollars(char **input, t_ee *ee);
void				copy_until_close_quote(char *l, int *i, char *copy, int *j);
void				copy_sorted_elements(char **sorted, char **sorted_env,
						int len);
int					calculate_sorted_len(char **sorted, t_ee *ee);
bool				copy_env_variables(char **tmp, t_ee *ee, int len_envp);
bool				copy_export_variables(char **tmp, t_ee *ee, int len_envp,
						int len_export);
int					find_export_var(char **export_list, int len_export,
						const char *arg);
void				add_export_var(char ***export_list, int *len_export,
						const char *arg);
void				add_env_var(char ***envp, int *len_envp, const char *arg);
void				update_env_var(char **envp, int index, const char *arg);
int					find_env_varrrr(char **envp, int len_envp, const char *arg);
void				handle_exit_with_status_value(char **a, t_ee *e,
						t_token *x);
void				handle_exit_with_numeric_value(char **a, t_ee *e,
						t_token *x);
int					handle_error_piperedi(const char *m, t_pipeline *p,
						char *t);
void				handle_exit_too_many_args(t_token *exit, char **args,
						t_ee *ee);

// cat "$PATH"

#endif
