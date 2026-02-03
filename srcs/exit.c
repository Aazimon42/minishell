/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:09:59 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/03 10:15:02 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(const char *s)
{
	long long	n;
	int			neg;
	int			i;

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
		n = n * 10 + (s[i++] - '0');
		if (!neg && n > 2147483647)
			return (0);
		if (neg && - n < -2147483648)
			return (0);
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

void	builtinexit(t_instru *instru, t_envar *head)
{
	int	errcode;

	if (!instru->next || (instru->next && instru->next->type == PIPE))
		errcode = 0;
	else if (instru->next && instru->next->next && instru->next->type == TEXT
		&& instru->next->next->type != PIPE)
		errcode = -1;
	else if (is_numeric(instru->next->str))
		errcode = ft_atoi(instru->next->str) % 256;
	else
		errcode = 255;
	free_instru(instru);
	free_envar(head);
	if (errcode == -1)
		print_error("exit: too many arguments \n");
	exit(errcode);
}
