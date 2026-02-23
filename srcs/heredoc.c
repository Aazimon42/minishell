/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:37:30 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/23 22:44:13 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_heredoc(char *str)
{
	int		fd[2];
	char	*line;
	pid_t	pid;
	int		save_stdin;

	pipe(fd);
	pid = fork();
	save_stdin = dup(STDIN_FILENO);
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, str) == 0)
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (save_stdin);
}

int	handle_heredoc(t_instru *instru)
{
	if (instru->next)
		return (ft_heredoc(instru->next->str));
	return (-1);
}
