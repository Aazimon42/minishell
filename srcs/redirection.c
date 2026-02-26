/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 16:40:02 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/26 19:26:43 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	next_sep_is_redirect(t_instru *instru)
{
	if (!instru)
		return (0);
	printf("grokkkipu");
	while (instru && instru->type == TEXT)
		instru = instru->next;
	if (instru && instru->type == SEPARATOR)
	{
		printf("salut daddy");
		printf("\nstrlen : %zu", ft_strlen(instru->str));
		printf("\nstr : %s\n",instru->str);
		if (ft_strlen(instru->str) == 1 && instru->str[0] == '>')
		{
			printf("jsuilapourtant");
			return (1);
		}
	}
	return (0);
}


int	handle_redirect(t_instru *instru)
{
	int	fd;

	printf("la");
	if (!instru->next && instru->next->type == TEXT)
		return (0);
	printf("ici");
	fd = open(instru->next->str, O_CREAT |  O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	printf("a cet endroit\n");
	dup2(fd, STDIN_FILENO);
	return (1);
}
