/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:25:40 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/10 18:53:18 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtincd(t_instru *instru, t_shell *shell)
{
	if (!instru->next || (instru->next->type != TEXT))
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd :");
		shell->exit_status = 1;
		return (1);
	}
	if (instru->next->str[0] == '~')
		transformtilde(instru->next);
	if (chdir(instru->next->str) == -1)
	{
		perror("cd :");
		shell->exit_status = 1;
		return (1);
	}
	shell->exit_status = 0;
	return (2);
}

int	builtinecho(t_instru *instru, t_shell *shell)
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
	shell->exit_status = 0;
	return (i);
}

int	builtinpwd(t_shell *shell)
{
	char	buffies[1024];

	if (getcwd(buffies, 1024) != NULL)
	{
		printf("%s\n", buffies);
		shell->exit_status = 0;
	}
	else
	{
		perror("getcwd");
		shell->exit_status = 1;
	}
	return (1);
}
