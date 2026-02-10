/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 08:11:26 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/10 18:29:24 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unquote_len(char *s1, int size)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	while (s1[i] && i < size)
	{
		if (s1[i] == '\'' || s1[i] == '"')
		{
			quote = s1[i++];
			while (s1[i] && s1[i] != quote)
			{
				len++;
				i++;
			}
			if (s1[i] == quote)
				i++;
		}
		i++;
		len++;
	}
	return (len);
}

char	*ft_unquote(char *s1, int size)
{
	int		i;
	int		j;
	char	quote;
	char	*s2;

	s2 = malloc(sizeof(char) * (ft_unquote_len(s1, size) + 1));
	i = 0;
	j = 0;
	while (s1[i] && i < size)
	{
		if (s1[i] == '\'' || s1[i] == '"')
		{
			quote = s1[i++];
			while (s1[i] && s1[i] != quote)
				s2[j++] = s1[i++];
			if (s1[i] == quote)
				i++;
		}
		s2[j++] = s1[i++];
	}
	s2[j] = '\0';
	return (s2);
}

char	*ft_strndup(char *s1, int size)
{
	char	*s2;
	int		i;

	s2 = ft_calloc(sizeof(char), size + 1);
	if (!s2)
		return (0);
	i = 0;
	while (s1[i] && i < size)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

t_instru	*clear_instru(t_instru *head)
{
	t_instru	*temp;

	while (head)
	{
		temp = head;
		free(head->str);
		head = head->next;
		free(temp);
	}
	return (NULL);
}

t_instru	*init_instruction(t_instru *before, char *value, int size, int type)
{
	t_instru	*temp;

	temp = malloc(sizeof(t_instru));
	if (!temp)
		return (NULL);
	if (before)
		before->next = temp;
	temp->pre = before;
	temp->str = ft_strndup(value, size);
	temp->unquoted = ft_unquote(value, size);
	temp->type = type;
	temp->next = NULL;
	return (temp);
}
