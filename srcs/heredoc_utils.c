/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 19:57:57 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/10 21:07:42 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_result(t_shell *shell, int status, int fd[2])
{
	if (((status & 0x7f) != 0) && ((status & 0x7f) != 0x7f))
	{
		close(fd[0]);
		shell->exit_status = 128 + (status & 0x7f);
		return (-2);
	}
	if (((status >> 8) & 0xff) == 130)
	{
		close(fd[0]);
		shell->exit_status = 130;
		return (-2);
	}
	return (-1);
}

void	exec_heredoc(t_shell *shell, int fd[2], char *delim, int exp)
{
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	close(shell->save_stdin);
	close(shell->save_stdout);
	read_heredoc(fd, delim, shell, exp);
	close(fd[1]);
}

int	quotes_closed(char *str)
{
	char	quote;

	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str++;
			while (*str && *str != quote)
				str++;
			if (!*str)
				return (0);
		}
		str++;
	}
	return (1);
}

int	has_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}
