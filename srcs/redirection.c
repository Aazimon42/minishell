/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:40:02 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/27 17:27:35 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	next_sep_is_redirect(t_instru *instru)
{
	if (!instru)
		return (0);
	while (instru && instru->type == TEXT)
		instru = instru->next;
	if (instru && instru->type == SEPARATOR)
	{
		if (ft_strlen(instru->str) == 1 && instru->str[0] == '>')
			return (1);
	}
	return (0);
}

int	handle_redirect(t_instru *instru)
{
	int	fd;

	if (!instru->next || !instru->next->str)
		return (-1);
	fd = open(instru->next->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		print_err("minishell: ");
		print_err(instru->next->str);
		print_err(": Permission denied\n");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	handle_append(t_instru *instru)
{
	int	fd;

	if (!instru->next || !instru->next->str)
		return (-1);
	fd = open(instru->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_err("minishell: ");
		print_err(instru->next->str);
		print_err(": Permission denied\n");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	handle_redirect_in(t_instru *instru)
{
	int	fd;

	if (!instru->next || !instru->next->str)
		return (-1);
	fd = open(instru->next->str, O_RDONLY);
	if (fd == -1)
	{
		print_err("minishell: ");
		print_err(instru->next->str);
		print_err(": Permission denied\n");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}
