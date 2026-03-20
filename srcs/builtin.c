/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:25:40 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/20 18:09:10 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtincd(t_instru *instru, t_envar *ev, t_shell *shell)
{
	char	buf[1024];
	char	*tmp;

	tmp = getcwd(buf, 1024);
	if (!instru->next || (instru->next->type != TEXT))
	{
		if (chdir(get_evvalue("HOME", ev)) == -1)
			perror("minishell: cd:");
		replace_envar(ev, ft_strdup("PWD"), ft_strdup(get_evvalue("HOME", ev)));
		replace_envar(ev, ft_strdup("OLDPWD"), ft_strdup(buf));
		shell->exit_status = 1;
		return (1);
	}
	transformtilde(instru->next, ev);
	if (chdir(instru->next->str) == -1)
	{
		print_err("minishell: cd: ");
		perror(instru->next->str);
		shell->exit_status = 1;
		return (1);
	}
	replace_envar(ev, ft_strdup("OLDPWD"), ft_strdup(tmp));
	replace_envar(ev, ft_strdup("PWD"), ft_strdup(getcwd(buf, 1024)));
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
	if (instru->next && ft_strncmp(instru->next->str, "-n", 2) == 0)
	{
		newline = 0;
		instru = instru->next;
		i++;
	}
	while (instru->next && instru->next->type == TEXT)
	{
		printf("%s", instru->next->unquoted);
		instru = instru->next;
		if (instru->next && instru->next->type == TEXT)
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

int	builtinenv(t_envar *head, t_shell *shell)
{
	print_env(head);
	shell->exit_status = 0;
	return (1);
}
