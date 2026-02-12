/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarhandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 08:03:35 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/11 18:54:18 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_evname(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	if (str[0] == '$')
		str++;
	while (str[i] && str[i] != ' ' && ft_isalnum(str[i]))
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	j = 0;
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

static char	*get_evvalue(char *str, t_envar *envar)
{
	while (envar)
	{
		if (strcmp(str, envar->name) == 0)
			return (envar->value);
		envar = envar->next;
	}
	return (NULL);
}

static void	replaceenvar(t_instru *head, char *name, char *value, int pos)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	k = 0;
	j = 0;
	i = 0;
	if (!name)
		return ;
	if (!value)
		value = "";
	result = malloc(ft_strlen(head->str) - ft_strlen(name) + ft_strlen(value) + 1);
	if (!result)
		return ;
	while (i < pos)
		result[j++] = head->str[i++];
	k = 0;
	while (value[k])
		result[j++] = value[k++];
	i = pos + ft_strlen(name) + 1;
	while (head->str[i])
		result[j++] = head->str[i++];
	result[j] = '\0';
	free(head->str);
	free(name);
	head->str = result;
}

static void	expand(t_instru *head, t_envar *envar)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*temp;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (head->str[i])
	{
		if (head->str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (head->str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (head->str[i] == '$' && head->str[i + 1]
			&& head->str[i + 1] != ' ' && !in_single)
		{
			temp = get_evname(&head->str[i]);
			replaceenvar(head, temp, get_evvalue(temp, envar), i);
			free(head->unquoted);
			head->unquoted = head->str;
			if (in_double)
				head->unquoted = ft_unquote(head->str, ft_strlen(head->str));
			i++;
		}
		i++;
	}
}

void	handle_envar(t_instru *head, t_envar *envar)
{
	while (head && head->type == TEXT)
	{
		expand(head, envar);
		head = head->next;
	}
}
