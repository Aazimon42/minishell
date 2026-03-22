/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:02:40 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/22 18:30:34 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_instru *instru)
{
	int	count;

	count = 0;
	while (instru)
	{
		if (instru->type == PIPE)
			count++;
		instru = instru->next;
	}
	return (count);
}

static void	exec_child(t_shell *shell, t_instru *instru, int fd_in, int fd_out)
{
	int			heredoc_fd;

	heredoc_fd = collect_heredocs(shell);
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
	apply_redirections(shell->instru, heredoc_fd);
	while (shell->instru && shell->instru->type == SEPARATOR)
	{
		shell->instru = shell->instru->next;
		if (shell->instru)
			shell->instru = shell->instru->next;
	}
	if (shell->instru)
		builtexec(shell);
	free_instru(instru);
	free_envar(shell->envhead);
	exit(shell->exit_status);
}

static int	run_pipe_segment(t_shell *shell, int fd_in, int *fd_out)
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
	{
		if (*fd_out != STDOUT_FILENO)
			close(pipefd[0]);
		exec_child(shell, shell->instru, fd_in, *fd_out);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (*fd_out != STDOUT_FILENO)
		close(pipefd[1]);
	return (pipefd[0]);
}

void	execute_pipeline(t_shell *shell, int i, int fd_in)
{
	int	n;
	int	fd_out;
	int	status;

	signal(SIGINT, handle_sigint_parent);
	n = count_pipes(shell->instru);
	while (i <= n)
	{
		fd_out = STDOUT_FILENO;
		if (i < n)
			fd_out = -1;
		fd_in = run_pipe_segment(shell, fd_in, &fd_out);
		if (fd_in == -1 && i < n)
			return ;
		shell->instru = skip_current_command(shell->instru);
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if ((status & 0x7f) == 0)
			shell->exit_status = (status >> 8) & 0xff;
		else if (((status & 0x7f) != 0) && ((status & 0x7f) != 0x7f))
			shell->exit_status = 128 + (status & 0x7f);
	}
	signal(SIGINT, handle_sigint);
}

void	fork_and_exec(t_shell *shell)
{
	pid_t	pid1;
	int		status;

	handle_envar(shell);
	signal(SIGINT, handle_sigint_parent);
	pid1 = fork();
	if (pid1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		executeve(shell);
		exit(shell->exit_status);
	}
	waitpid(pid1, &status, 0);
	signal(SIGINT, handle_sigint);
	if (((status & 0x7f) != 0) && ((status & 0x7f) != 0x7f)
		&& ((status & 0x7f) == SIGQUIT))
		write(1, "Quit (core dumped)\n", 19);
	if ((status & 0x7f) == 0)
		shell->exit_status = (status >> 8) & 0xff;
	else if (((status & 0x7f) != 0) && ((status & 0x7f) != 0x7f))
		shell->exit_status = 128 + (status & 0x7f);
}
