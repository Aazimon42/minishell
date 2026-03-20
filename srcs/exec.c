/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:43:03 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/20 12:55:59 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executeve(t_shell *shell)
{
	char	**split_cmd;
	char	*cmd;
	char	*path;
	char	**env;

	cmd = ft_join_instru(shell->instru);
	env = split_env(shell->envhead);
	split_cmd = ft_split(cmd, ' ');
	if (split_cmd[0] && access(split_cmd[0], F_OK) == 0)
		path = split_cmd[0];
	else
		path = get_cmd(split_cmd[0], env);
	free(cmd);
	free_instru(shell->instru);
	free_envar(shell->envhead);
	handle_error(shell, env, split_cmd, path);
	execve(path, split_cmd, env);
	print_err("minishell: execve: format error\n");
	free2d(env);
	free2d(split_cmd);
	restore_fds(shell->save_stdin, shell->save_stdout);
	exit(126);
}

int	builtexec(t_shell *shell)
{
	int		executed;

	handle_envar(shell);
	executed = 0;
	if (!ft_strcmp(shell->instru->unquoted, "cd"))
		executed += builtincd(shell->instru, shell->envhead, shell);
	else if (!ft_strcmp(shell->instru->unquoted, "echo"))
		executed += builtinecho(shell->instru, shell);
	else if (!ft_strcmp(shell->instru->unquoted, "pwd"))
		executed += builtinpwd(shell);
	else if (!ft_strcmp(shell->instru->unquoted, "export"))
		executed += builtinexport(shell->instru, shell->envhead, shell, 0);
	else if (!ft_strcmp(shell->instru->unquoted, "unset"))
		executed += builtinunset(shell->instru, shell->envhead, shell);
	else if (!ft_strcmp(shell->instru->unquoted, "env"))
		executed += builtinenv(shell->envhead, shell);
	else if (!ft_strcmp(shell->instru->unquoted, "exit"))
		builtinexit(shell->instru, shell->envhead, shell);
	else
		fork_and_exec(shell);
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
	while (tmp && tmp->type != PIPE)
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

int	execute_one_command(t_shell *shell)
{
	t_instru	*head;

	head = shell->instru;
	shell->save_stdin = dup(STDIN_FILENO);
	shell->save_stdout = dup(STDOUT_FILENO);
	if (!apply_redirections(shell->instru, collect_heredocs(shell)))
	{
		restore_fds(shell->save_stdin, shell->save_stdout);
		return (0);
	}
	while (shell->instru && shell->instru->type == SEPARATOR)
	{
		shell->instru = shell->instru->next;
		if (shell->instru)
			shell->instru = shell->instru->next;
	}
	if (shell->instru)
		builtexec(shell);
	restore_fds(shell->save_stdin, shell->save_stdout);
	shell->instru = head;
	return (1);
}

void	execute(t_shell *shell)
{
	if (!check_syntax(shell->instru))
		return ;
	if (count_pipes(shell->instru) > 0)
	{
		execute_pipeline(shell, 0, STDIN_FILENO);
		return ;
	}
	while (shell->instru)
	{
		execute_one_command(shell);
		shell->instru = skip_current_command(shell->instru);
	}
}
