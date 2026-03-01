/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:37:30 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/01 20:03:41 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	read_heredoc(int fd_write, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
	close(fd_write);
	exit(0);
}

int	read_heredoc_to_fd(char *delimiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		read_heredoc(fd[1], delimiter);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}

int	handle_heredoc(t_instru *instru)
{
	int	fd;

	if (!instru->next || !instru->next->str)
		return (-1);
	fd = read_heredoc_to_fd(instru->next->str);
	if (fd == -1)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	collect_heredocs(t_instru *cmd)
{
	t_instru	*tmp;
	int			last_fd;
	int			fd;

	last_fd = -1;
	tmp = cmd;
	while (tmp && (tmp->type != SEPARATOR || ft_strcmp(tmp->str, "|")))
	{
		if (get_redir_type(tmp) == R_HEREDOC)
		{
			if (!tmp->next || !tmp->next->str)
				return (-2);
			fd = read_heredoc_to_fd(tmp->next->str);
			if (fd == -1)
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
