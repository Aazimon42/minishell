/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:25:40 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/10 14:38:01 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtincd(t_instru *instru)
{
	if (!instru->next || (instru->next->type != TEXT))
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd :");
		return (1);
	}
	if (instru->next->str[0] == '~')
		transformtilde(instru->next);
	if (chdir(instru->next->str) == -1)
	{
		perror("cd :");
		return (1);
	}
	return (2);
}

int	builtinecho(t_instru *instru)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	if (!instru)
		return (0);
	if (instru->next && ft_strncmp(instru->next->str, "-n", 3) == 0)
	{
		newline = 0;
		instru = instru->next;
		i++;
	}
	while (instru->next && instru->next->type == TEXT)
	{
		printf("%s", instru->next->unquoted);
		instru = instru->next;
		if (instru && instru->type == TEXT)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (i);
}

int	builtinpwd(void)
{
	char	buffies[1024];

	if (getcwd(buffies, 1024) != NULL)
		printf("%s\n", buffies);
	else
		perror("getcwd");
	return (1);
}
