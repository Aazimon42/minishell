/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:01 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/10 20:44:28 by edi-maio         ###   ########.fr       */
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

# define RED "\033[91m"
# define ORANGE "\033[93m"
# define YELLOW "\033[93m"
# define GREEN "\033[92m"
# define CYAN "\001\033[36m\002"
# define BLUE "\033[94m"
# define INDIGO "\033[95m"
# define VIOLET "\033[95m"
# define RESET "\033[0m"

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

t_instru	*init_instruction(t_instru *before,
				char *value, int size, int type);
t_instru	*slicer(char *str);
void		free_instru(t_instru *instru);
void		free2d(char **arr);
int			builtincd(t_instru *instru, t_shell *shell);
int			builtinecho(t_instru *instru, t_shell *shell);
int			builtinpwd(t_shell *shell);
int			builtinexport(t_instru *instru, t_envar *envhead, t_shell *shell);
void		transformtilde(t_instru *instru);
void		execute(t_shell *shell);
t_envar		*setup_envar(char **env);
void		add_envar(char *name, char *value, t_envar *head);
t_envar		*setup_envar(char **env);
int			ft_strcmp(const char *s1, const char *s2);
char		*get_envar_name(char *str);
char		*get_envar_value(char *str);
void		print_env(t_envar *head);
void		print_export(t_envar *head);
int			builtinunset(t_instru *instru, t_envar *head, t_shell *shell);
int			builtinenv(t_envar *head, t_shell *shell);
void		print_error(char *str);
void		builtinexit(t_instru *instru, t_envar *head, t_shell *shell);
char		*get_var(t_envar *head, char *name, int i);
void		handle_envar(t_shell *shell);
char		*expand(char *str, t_shell *shell, int in_s, int in_d);
char		*ft_unquote(char *s1, int size);
char		*get_cmd(char *cmd, char **env);
void		ft_strcpy(char *dest, char *src);
void		ft_strcat(char *dest, char *src);
char		**split_env(t_envar *envhead);
int			handle_heredoc(t_shell *shell);
int			handle_redirect(t_instru *instru);
int			next_sep_is_redirect(t_instru *instru);
char		*ft_join_instru(t_instru *instru);
t_redir		get_redir_type(t_instru *node);
void		restore_fds(int save_stdin, int save_stdout);
t_instru	*skip_current_command(t_instru *node);
int			collect_heredocs(t_shell *shell);
int			handle_append(t_instru *instru);
int			handle_redirect_in(t_instru *instru);
int			is_fullalnum(char *str);
int			apply_redirections(t_instru *cmd, int heredoc_fd);
void		executeve(t_shell *shell);
void		fork_and_exec(t_shell *shell);
int			count_pipes(t_instru *instru);
void		execute_pipeline(t_shell *shell, int i, int fd_in);
int			builtexec(t_shell *shell);
void		formatenv(char *env, t_envar *envhead);
void		replace_envar(t_envar *head, char *name, char *value);
void		increment_double_int(int *i, int *j);
int			find_and_replace_env(t_envar *tmp, char *name, t_instru *instru);
void		free_envar(t_envar *head);
void		handle_error(char **env, char **split_cmd, char *path);
void		handle_sigint(int sig);
void		handle_sigint_parent(int sig);
int			handle_error_builtinexport(char *str, t_shell *shell);
void		handle_sigquit(int sig);
int			quotes_closed(char *str);
int			has_quotes(char *str);
void		read_heredoc(int fd[2], char *delimiter,
				t_shell *shell, int exp);
void		exec_heredoc(t_shell *shell, int fd[2], char *delim, int exp);
int			handle_result(t_shell *shell, int status, int fd[2]);

#endif
