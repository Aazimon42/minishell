/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:45:17 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/23 18:42:30 by edi-maio         ###   ########.fr       */
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

void	print_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
}

void	transformtilde(t_instru *instru)
{
	char	*tofree;

	tofree = instru->str;
	if (instru->str[0] == '~')
	{
		instru->str = ft_strjoin(getenv("HOME"), instru->str + 1);
		free(tofree);
	}
}

void	free2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
