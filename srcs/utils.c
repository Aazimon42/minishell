/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:45:17 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/24 16:13:46 by edi-maio         ###   ########.fr       */
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

static char	**fill_split(t_instru	*instru, char **split_cmd, int size)
{
	int	i;

	i = 0;
	while (split_cmd && i < size)
	{
		if (instru && instru->type == SEPARATOR)
		{
			instru = instru->next;
			if (instru->next)
				instru = instru->next;
			continue ;
		}
		split_cmd[i] = ft_strdup(instru->unquoted);
		instru = instru->next;
		if (!split_cmd[i])
		{
			free2d(split_cmd);
			return (0);
		}
		i++;
	}
	split_cmd[i] = NULL;
	return (split_cmd);
}

char	**split_instru(t_instru *instru)
{
	int			size;
	t_instru	*tmp;
	char		**split_cmd;

	size = 0;
	tmp = instru;
	while (instru && instru->type != PIPE)
	{
		if (instru && instru->type == SEPARATOR)
		{
			instru = instru->next;
			if (instru->next)
				instru = instru->next;
			continue ;
		}
		instru = instru->next;
		size++;
	}
	split_cmd = malloc(sizeof(char *) * (size + 1));
	split_cmd = fill_split(tmp, split_cmd, size);
	return (split_cmd);
}
