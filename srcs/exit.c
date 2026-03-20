/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:09:59 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/20 18:31:33 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(const char *s)
{
	unsigned long long	n;
	int					neg;
	int					i;

	n = 0;
	i = 0;
	neg = 0;
	if (!s || !s[0])
		return (0);
	if (s[0] == '-' || s[0] == '+')
		neg = (s[i++] == '-');
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		if ((!neg && n > (9223372036854775807ULL - (s[i] - '0')) / 10)
			|| (neg && n > (9223372036854775808ULL - (s[i] - '0')) / 10))
			return (0);
		n = n * 10 + (s[i++] - '0');
	}
	return (1);
}

void	free_instru(t_instru *instru)
{
	t_instru	*temp;

	temp = NULL;
	while (instru)
	{
		free(instru->str);
		free(instru->unquoted);
		temp = instru->next;
		free(instru);
		instru = temp;
	}
}

void	free_envar(t_envar *head)
{
	t_envar	*temp;

	temp = NULL;
	while (head)
	{
		free(head->value);
		free(head->name);
		temp = head->next;
		free(head);
		head = temp;
	}
}

void	builtinexit(t_instru *instru, t_envar *head, t_shell *shell)
{
	long long	errcode;

	print_err("exit\n");
	if (!instru->next || instru->next->type == PIPE)
		errcode = shell->exit_status;
	else if (instru->next && !is_numeric(instru->next->str))
	{
		shell->exit_status = 2;
		print_err("minishell: exit: ");
		print_err(instru->next->str);
		print_err(": numeric argument required\n");
		errcode = 2;
	}
	else if (instru->next->next && instru->next->next->type != PIPE)
	{
		shell->exit_status = 1;
		print_err("minishell : exit : too many arguments\n");
		return ;
	}
	else
		errcode = ft_atoi(instru->next->str) % 256;
	free_instru(instru);
	free_envar(head);
	restore_fds(shell->save_stdin, shell->save_stdout);
	exit(errcode);
}
