/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:18:05 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/10 15:20:03 by edi-maio         ###   ########.fr       */
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

void	handle_error(char **env, char **split_cmd, char *path)
{
	if (!path)
	{
		print_error("minishell: ");
		print_error(split_cmd[0]);
		print_error(": command not found\n");
		free2d(env);
		exit(127);
	}
	if (access(path, X_OK) != 0)
	{
		print_error("minishell: ");
		print_error(path);
		print_error(": Permission denied\n");
		free2d(env);
		exit(126);
	}
}
