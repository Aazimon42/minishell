/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:37:30 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/10 21:46:14 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_delimiter(char *line, char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	read_heredoc(int fd[2], char *delimiter, t_shell *shell, int exp)
{
	char	*line;
	char	*result;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[1]);
			exit(130);
		}
		if (check_delimiter(line, delimiter))
			break ;
		result = line;
		if (exp)
			result = expand(line, shell, 0, 0);
		write(fd[1], result, ft_strlen(result));
		write(fd[1], "\n", 1);
		free(line);
		if (result != line)
			free(result);
	}
	close(fd[1]);
	exit(0);
}

static int	read_heredoc_to_fd(t_instru *instru, t_shell *shell, int exp)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	char	*clean_delim;

	exp = quotes_closed(instru->str) && !has_quotes(instru->str);
	clean_delim = instru->unquoted;
	if (!quotes_closed(instru->str))
		clean_delim = "\x01";
	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, handle_sigint_parent);
	pid = fork();
	if (pid == 0)
		exec_heredoc(shell, fd, clean_delim, exp);
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (handle_result(shell, status, fd) == -2)
		return (-2);
	return (fd[0]);
}

int	handle_heredoc(t_shell *shell)
{
	int	fd;

	if (!shell->instru->next || !shell->instru->next->str)
		return (-1);
	fd = read_heredoc_to_fd(shell->instru->next, shell, 0);
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
			fd = read_heredoc_to_fd(tmp->next, shell, 0);
			if (last_fd != -1)
				close(last_fd);
			if (fd == -1 || fd == -2)
				return (-2);
			last_fd = fd;
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (last_fd);
}
