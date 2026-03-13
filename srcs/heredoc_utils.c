/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 19:57:57 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/13 01:36:07 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_delimiter(char *line, char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
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

int	handle_heredoc_end(int fd[2], t_shell *shell, char *delimiter)
{
	close(fd[1]);
	if (g_exit_status == 130)
	{
		shell->exit_status = 130;
		signal(SIGINT, handle_sigint);
		return (-2);
	}
	print_err("minishell: warning: here-document"
		" at line 1 delimited by end-of-file (wanted `");
	print_err(delimiter);
	print_err("')\n");
	return (0);
}
