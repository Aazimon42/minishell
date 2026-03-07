/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:37:30 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/07 10:17:41 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	read_heredoc(int fd_write, char *delimiter,
						t_envar *envhead, t_shell *shell)
{
	char	*line;
	char	*result;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd_write);
			kill(getpid(), SIGINT);
			exit(130);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		result = expand(line, envhead, shell);
		write(fd_write, result, ft_strlen(result));
		write(fd_write, "\n", 1);
		free(line);
		free(result);
	}
	close(fd_write);
	exit(0);
}

static int	read_heredoc_to_fd(char *delimiter,
							t_envar *envhead, t_shell *shell)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, handle_sigint_parent);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		read_heredoc(fd[1], delimiter, envhead, shell);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (((status & 0x7f) != 0) && ((status & 0x7f) != 0x7f))
	{
		shell->exit_status = 128 + (status & 0x7f);
		close(fd[0]);
		return (-2);
	}
	return (fd[0]);
}

int	handle_heredoc(t_shell *shell)
{
	int	fd;

	if (!shell->instru->next || !shell->instru->next->str)
		return (-1);
	fd = read_heredoc_to_fd(shell->instru->next->str, shell->envhead, shell);
	if (fd == -1)
		return (-1);
	if (fd == -2)
		return (-2);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	collect_heredocs(t_shell *shell)
{
	t_instru	*tmp;
	int			last_fd;
	int			fd;

	last_fd = -1;
	tmp = shell->instru;
	while (tmp && (tmp->type != SEPARATOR || ft_strcmp(tmp->str, "|")))
	{
		if (get_redir_type(tmp) == R_HEREDOC)
		{
			if (!tmp->next || !tmp->next->str)
				return (-2);
			fd = read_heredoc_to_fd(tmp->next->str, shell->envhead, shell);
			if (fd == -1 || fd == -2)
				return (-2);
			if (last_fd != -1)
				close(last_fd);
			last_fd = fd;
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (last_fd);
}
