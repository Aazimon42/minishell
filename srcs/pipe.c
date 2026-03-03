/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:02:40 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/03 18:34:54 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_instru *instru)
{
	int	count;

	count = 0;
	while (instru)
	{
		if (instru->type == SEPARATOR && !ft_strcmp(instru->str, "|"))
			count++;
		instru = instru->next;
	}
	return (count);
}

static void	exec_child(t_instru *cmd, t_envar *env, int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	apply_redirections(cmd, collect_heredocs(cmd));
	executeve(cmd, env);
	exit(1);
}

static int	run_pipe_segment(t_instru *cmd, t_envar *env, int fd_in, int *fd_out)
{
	int		pipefd[2];
	pid_t	pid;

	if (*fd_out != STDOUT_FILENO)
	{
		if (pipe(pipefd) == -1)
			return (-1);
		*fd_out = pipefd[1];
	}
	else
		pipefd[0] = -1;
	pid = fork();
	if (pid == 0)
		exec_child(cmd, env, fd_in, *fd_out);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
	return (pipefd[0]);
}

void	execute_pipeline(t_instru *instru, t_envar *env)
{
	int			n;
	int			i;
	int			fd_in;
	int			fd_out;
	t_instru	*cmd;

	n = count_pipes(instru);
	fd_in = STDIN_FILENO;
	cmd = instru;
	i = 0;
	while (i <= n)
	{
		fd_out = (i < n) ? -1 : STDOUT_FILENO;
		fd_in = run_pipe_segment(cmd, env, fd_in, &fd_out);
		if (fd_in == -1 && i < n)
			return ;
		cmd = skip_current_command(cmd);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	fork_and_exec(t_instru *instru, t_envar *envhead)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		executeve(instru, envhead);
		exit(1);
	}
	waitpid(pid1, NULL, 0);
}
