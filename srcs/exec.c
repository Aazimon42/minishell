/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:43:03 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/01 20:17:24 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executeve(t_instru *instru, t_envar *envhead)
{
	char	**split_cmd;
	char	*cmd;
	char	*path;
	char	**env;

	cmd = ft_join_instru(instru);
	env = split_env(envhead);
	split_cmd = ft_split(cmd, ' ');
	if (access(split_cmd[0], F_OK | X_OK) == 0)
		path = split_cmd[0];
	else
		path = get_cmd(split_cmd[0], env);
	free(cmd);
	if (!path || execve(path, split_cmd, env) == -1)
	{
		if (path)
			free(path);
		free2d(env);
		return ;
	}
}

static int	builtexec(t_instru *instru, t_envar *envhead)
{
	int		executed;
	pid_t	pid1;

	executed = 0;
	if (!ft_strcmp(instru->str, "cd"))
		executed += builtincd(instru);
	else if (!ft_strcmp(instru->str, "echo"))
		executed += builtinecho(instru);
	else if (!ft_strcmp(instru->str, "pwd"))
		executed += builtinpwd();
	else if (!ft_strcmp(instru->str, "export"))
		executed += builtinexport(instru, envhead);
	else if (!ft_strcmp(instru->str, "unset"))
		executed += builtinunset(instru, envhead);
	else if (!ft_strcmp(instru->str, "env"))
		executed += builtinenv(envhead);
	else if (!ft_strcmp(instru->str, "exit"))
		builtinexit(instru, envhead);
	else
	{
		pid1 = fork();
		if (pid1 == 0)
			executeve(instru, envhead);
		waitpid(pid1, NULL, 0);
		if (pid1 == 0)
			exit(0);
		executed = 1;
	}
	return (executed);
}

int	apply_redirections(t_instru *cmd, int heredoc_fd)
{
	t_instru	*tmp;
	int			separator;

	if (heredoc_fd == -2)
		return (0);
	if (heredoc_fd != -1)
		dup2(heredoc_fd, STDIN_FILENO);
	if (heredoc_fd != -1)
		close(heredoc_fd);
	tmp = cmd;
	while (tmp && (tmp->type != SEPARATOR || ft_strcmp(tmp->str, "|")))
	{
		separator = get_redir_type(tmp);
		if (separator == R_OUT)
			handle_redirect(tmp);
		else if (separator == R_APPEND)
			handle_append(tmp);
		else if (separator == R_IN)
			handle_redirect_in(tmp);
		if (separator)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

int	execute_one_command(t_instru *cmd, t_envar *env)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (!apply_redirections(cmd, collect_heredocs(cmd)))
	{
		restore_fds(save_stdin, save_stdout);
		return (0);
	}
	builtexec(cmd, env);
	restore_fds(save_stdin, save_stdout);
	return (1);
}

void	execute(t_instru *instru, t_envar *envhead)
{
	while (instru)
	{
		execute_one_command(instru, envhead);
		instru = skip_current_command(instru);
	}
}
