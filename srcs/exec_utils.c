/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:18:05 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/24 15:52:28 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

t_redir	get_redir_type(t_instru *node)
{
	if (!node || node->type != SEPARATOR || !node->str)
		return (R_NONE);
	if (!ft_strcmp(node->str, "<"))
		return (R_IN);
	if (!ft_strcmp(node->str, ">"))
		return (R_OUT);
	if (!ft_strcmp(node->str, ">>"))
		return (R_APPEND);
	if (!ft_strcmp(node->str, "<<"))
		return (R_HEREDOC);
	return (R_NONE);
}

void	restore_fds(int save_stdin, int save_stdout)
{
	if (save_stdin != -1)
	{
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
	}
	if (save_stdout != -1)
	{
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdout);
	}
}

t_instru	*skip_current_command(t_instru *node)
{
	t_instru	*temp;

	while (node)
	{
		if (node->type == PIPE)
		{
			temp = node->next;
			free(node->str);
			free(node->unquoted);
			free(node);
			return (temp);
		}
		temp = node->next;
		free(node->str);
		free(node->unquoted);
		free(node);
		node = temp;
	}
	return (NULL);
}

void	handle_error(t_shell *shell, char **env, char **split_cmd, char *path)
{
	int	err;

	if (!*split_cmd)
		err = 0;
	else if (!path)
	{
		print_err("minishell: ");
		print_err(split_cmd[0]);
		print_err(": command not found\n");
		err = 127;
	}
	else if (access(path, X_OK) != 0)
	{
		print_err("minishell: ");
		print_err(path);
		print_err(": Permission denied\n");
		err = 126;
	}
	else
		return ;
	free2d(split_cmd);
	free2d(env);
	restore_fds(shell->save_stdin, shell->save_stdout);
	exit(err);
}

int	check_syntax(t_instru *instru)
{
	t_instru	*tmp;

	tmp = instru;
	if (tmp && tmp->type == PIPE)
	{
		print_err("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	while (tmp && tmp->next)
	{
		if (tmp->type == SEPARATOR && tmp->next && tmp->next->type == SEPARATOR)
		{
			print_err("minishell: syntax error near unexpected token `");
			print_err(tmp->next->str);
			print_err("'\n");
			return (0);
		}
		tmp = tmp->next;
	}
	if (tmp && tmp->type != TEXT)
	{
		print_err("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}
