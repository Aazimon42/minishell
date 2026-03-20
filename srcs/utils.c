/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:45:17 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/20 15:58:38 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var(t_envar *head, char *name, int i)
{
	while (head)
	{
		if (!ft_strncmp(head->name, name, i))
			return (head->value);
		head = head->next;
	}
	return (0);
}

void	print_err(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	write(2, str, len);
}

void	transformtilde(t_instru *instru, t_envar *envhead)
{
	char	*tofree;
	char	*tmp;

	tofree = instru->str;
	if (instru->str[0] == '~')
	{
		tmp = get_evvalue("HOME", envhead);
		if (!tmp)
			return ;
		instru->str = ft_strjoin(tmp, instru->str + 1);
		free(tofree);
	}
	if (instru->str[0] == '-' && ft_strlen(instru->str) == 1)
	{
		instru->str = ft_strdup(get_evvalue("OLDPWD", envhead));
		free(tofree);
	}
}
