/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 05:24:02 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/10 17:50:12 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_envar_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	name[i] = '\0';
	i--;
	while (i >= 0)
	{
		name[i] = str[i];
		i--;
	}
	return (name);
}

char	*get_envar_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	value = malloc(sizeof(char) * (ft_strlen(&str[i]) + 1));
	if (!value)
		return (NULL);
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

static t_envar	*init_envar(char *name, char *value)
{
	t_envar	*result;

	result = malloc(sizeof(t_envar));
	if (!result)
		return (NULL);
	result->next = NULL;
	result->name = name;
	result->value = value;
	return (result);
}

void	add_envar(char *name, char *value, t_envar *head)
{
	t_envar	*result;

	if (!head)
		return ;
	while (head->next)
	{
		head = head->next;
	}
	result = malloc(sizeof(t_envar));
	if (!result)
		return ;
	result->next = NULL;
	result->name = name;
	result->value = value;
	head->next = result;
}

t_envar	*setup_envar(char **env)
{
	int		i;
	t_envar	*head;

	i = 1;
	if (!env)
		return (0);
	head = init_envar(get_envar_name(env[0]), get_envar_value(env[0]));
	if (!head)
		return (0);
	while (env[i])
	{
		add_envar(get_envar_name(env[i]), get_envar_value(env[i]), head);
		i++;
	}
	return (head);
}
