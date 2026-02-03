/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 08:11:26 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/03 08:35:31 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	temp->type = type;
	temp->next = NULL;
	temp->quotetype = 0;
	handle_quote_type(temp);
	return (temp);
}
