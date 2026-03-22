/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:01 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/22 17:55:48 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

# define RED     "\001\033[91m\002"
# define ORANGE  "\001\033[93m\002"
# define YELLOW  "\001\033[93m\002"
# define GREEN   "\001\033[92m\002"
# define CYAN    "\001\033[36m\002"
# define BLUE    "\001\033[94m\002"
# define INDIGO  "\001\033[95m\002"
# define VIOLET  "\001\033[95m\002"
# define RESET   "\001\033[0m\002"
# define TEXT 1
# define SEPARATOR 2
# define PIPE 3

typedef struct s_instruction
{
	struct s_instruction	*pre;
	struct s_instruction	*next;
	char					*str;
	char					*unquoted;
	int						type;
}		t_instru;

typedef struct s_envar
{
	struct s_envar	*next;
	char			*name;
	char			*value;
}				t_envar;

typedef struct s_shell
{
	t_instru	*instru;
	t_envar		*envhead;
	int			exit_status;
	int			save_stdin;
	int			save_stdout;
	int			tty;
}				t_shell;

typedef enum e_redir
{
	R_NONE = 0,
	R_IN = 1,
	R_OUT = 2,
	R_APPEND = 3,
	R_HEREDOC = 4
}	t_redir;

extern int	g_exit_status;

// ===== PARSING =====
t_instru	*init_instruction(t_instru *before,
				char *value, int size, int type);
t_instru	*slicer(char *str);
int			check_syntax(t_instru *instru);

// ===== EXECUTION =====
void		execute(t_shell *shell);
int			builtexec(t_shell *shell);
void		executeve(t_shell *shell);
void		fork_and_exec(t_shell *shell);

// ===== PIPELINE =====
int			count_pipes(t_instru *instru);
void		execute_pipeline(t_shell *shell, int i, int fd_in);
int			apply_redirections(t_instru *cmd, int heredoc_fd);

// ===== REDIRECTIONS =====
int			handle_redirect(t_instru *instru);
int			handle_redirect_in(t_instru *instru);
int			handle_append(t_instru *instru);
int			next_sep_is_redirect(t_instru *instru);
t_redir		get_redir_type(t_instru *node);

// ===== HEREDOC =====
int			handle_heredoc(t_shell *shell);
int			collect_heredocs(t_shell *shell);
int			handle_heredoc_end(int fd[2], t_shell *shell, char *delimiter);
int			check_delimiter(char *line, char *delimiter);
int			quotes_closed(char *str);
int			has_quotes(char *str);

// ===== BUILTINS =====
int			builtincd(t_instru *instru, t_envar *envhead, t_shell *shell);
int			builtinecho(t_instru *instru, t_shell *shell);
int			builtinpwd(t_shell *shell);
int			builtinexport(t_instru *instru, t_envar *envhead,
				t_shell *shell, int found);
int			builtinunset(t_instru *instru, t_envar *head, t_shell *shell);
int			builtinenv(t_envar *head, t_shell *shell);
void		builtinexit(t_instru *instru, t_envar *head, t_shell *shell);

// ===== ENVIRONMENT =====
t_envar		*setup_envar(char **env);
void		add_envar(char *name, char *value, t_envar *head);
char		*get_envar_name(char *str);
char		*get_envar_value(char *str);
void		replace_envar(t_envar *head, char *name, char *value);
int			find_and_replace_env(t_envar *tmp, char *name, t_instru *instru);
char		*get_var(t_envar *head, char *name, int i);
char		**split_env(t_envar *envhead);
void		formatenv(char *env, t_envar *envhead);
void		handle_envar(t_shell *shell);
char		*expand(char *str, t_shell *shell, int in_s, int in_d);
char		*get_cmd(char *cmd, char **env);
char		*get_evvalue(char *str, t_envar *envar);

// ===== PRINT / ENV DISPLAY =====
void		print_env(t_envar *head);
void		print_export(t_envar *head);
void		print_err(char *str);

// ===== SIGNALS =====
void		handle_sigint(int sig);
void		handle_sigint_parent(int sig);
void		handle_sigint_heredoc(int sig);

// ===== MEMORY / FREE =====
void		free_instru(t_instru *instru);
void		free_envar(t_envar *head);
void		free2d(char **arr);

// ===== UTILS =====
void		restore_fds(int save_stdin, int save_stdout);
t_instru	*skip_current_command(t_instru *node);
void		handle_error(t_shell *shell, char **env,
				char **split_cmd, char *path);
int			handle_error_builtinexport(char *str, t_shell *shell);
void		transformtilde(t_instru *instru, t_envar *envhead);
char		**split_instru(t_instru *instru);
char		*ft_unquote(char *s1, int size);
void		increment_double_int(int *i, int *j);
int			is_fullalnum(char *str);

// ===== STRING UTILS =====
int			ft_strcmp(const char *s1, const char *s2);
void		ft_strcpy(char *dest, char *src);
void		ft_strcat(char *dest, char *src);

#endif
