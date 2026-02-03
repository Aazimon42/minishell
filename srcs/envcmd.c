/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:18:34 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/03 09:46:44 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_envar(t_envar *head, char *name, char *value)
{
	if (ft_strlen(value) == 0)
	{
		free(value);
		return ;
	}
	while (head)
	{
		if (!ft_strcmp(head->name, name))
		{
			free(head->value);
			head->value = value;
		}
		head = head->next;
	}
}

t_envar	*delete_envar(t_envar *head, char *name)
{
	t_envar	*tmp;
	t_envar	*prev;

	tmp = head;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (prev)
				prev->next = tmp->next;
			else
				head = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (head);
}

int	builtinexport(t_instru *instru, t_envar *envar)
{
	int		i;
	char	*name;
	int		found;
	t_envar	*tmp;

	i = 1;
	if (!instru->next || instru->next->type != TEXT)
	{
		print_export(envar);
		return (i);
	}
	while (instru->next && instru->next->type == TEXT)
	{
		found = 0;
		tmp = envar;
		name = get_envar_name(instru->next->unquoted);
		i += 1;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, name))
			{
				replace_envar(envar, name, get_envar_value(instru->next->unquoted));
				found = 1;
			}
			tmp = tmp->next;
		}
		if (!found)
			add_envar(name, get_envar_value(instru->next->unquoted), envar);
		instru = instru->next;
	}
	return (i);
}

int	builtinenv(t_envar *head)
{
	print_env(head);
	return (1);
}

int	builtinunset(t_instru *instru, t_envar *head)
{
	int		i;
	char	*name;

	i = 1;
	if (!instru->next || instru->next->type != TEXT)
	{
		print_error("unset: not enough arguments\n");
		return (i);
	}
	while (instru->next && instru->next->type == TEXT)
	{
		name = get_envar_name(instru->next->unquoted);
		delete_envar(head, name);
		free(name);
		instru = instru->next;
		i++;
	}
	return (i);
}
