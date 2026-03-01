/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:18:05 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/01 20:03:34 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (node)
	{
		if (node->type == SEPARATOR
			&& node->str
			&& !ft_strcmp(node->str, "|"))
		{
			if (node->next)
				return (node->next);
			return (NULL);
		}
		node = node->next;
	}
	return (NULL);
}
