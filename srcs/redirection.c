/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:40:02 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/26 19:55:01 by edi-maio         ###   ########.fr       */
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
		return (0);
	fd = open(instru->next->next->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
