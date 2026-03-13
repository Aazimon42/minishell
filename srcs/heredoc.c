/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:37:30 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/13 01:34:40 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	write_line(int fd, char *line, t_shell *shell, int exp)
{
	char	*result;

	result = line;
	if (!line)
		return ;
	if (exp)
		result = expand(line, shell, 0, 0);
	write(fd, result, ft_strlen(result));
	write(fd, "\n", 1);
	if (result != line)
		free(result);
}

static int	read_heredoc_lines(int fd[2], char *delim, t_shell *shell, int exp)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (handle_heredoc_end(fd, shell, delim) == -2)
				return (-2);
			return (0);
		}
		if (check_delimiter(line, delim))
			break ;
		write_line(fd[1], line, shell, exp);
		free(line);
	}
	close(fd[1]);
	signal(SIGINT, handle_sigint);
	return (0);
}

static int	read_heredoc_to_fd(t_instru *instru, t_shell *shell, int exp)
{
	int		fd[2];
	char	*clean_delim;

	exp = quotes_closed(instru->str) && !has_quotes(instru->str);
	clean_delim = instru->unquoted;
	if (!quotes_closed(instru->str))
		clean_delim = "\x01";
	if (pipe(fd) == -1)
		return (-1);
	if (read_heredoc_lines(fd, clean_delim, shell, exp) == -2)
	{
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
