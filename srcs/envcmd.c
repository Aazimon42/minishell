/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:18:34 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/13 18:24:54 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_envar(t_envar *head, char *name, char *value)
{
	if (!name || !value)
		return ;
	while (head)
	{
		if (!ft_strcmp(head->name, name))
		{
			free(head->value);
			head->value = value;
		}
		head = head->next;
	}
	free(name);
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

int	builtinexport(t_instru *instru, t_envar *envar, t_shell *shell, int found)
{
	int		i;
	char	*name;
	t_envar	*tmp;

	i = 1;
	if (!instru->next || instru->next->type != TEXT)
	{
		print_export(envar);
		return (i);
	}
	while (instru->next && instru->next->type == TEXT && !found)
	{
		tmp = envar;
		name = get_envar_name(instru->next->unquoted);
		if (!handle_error_builtinexport(name, shell))
			return (i);
		i += 1;
		found = find_and_replace_env(tmp, name, instru);
		if (!found)
			add_envar(name, get_envar_value(instru->next->str), envar);
		instru = instru->next;
	}
	shell->exit_status = 0;
	return (i);
}

void	handle_envar(t_shell *shell)
{
	t_instru	*head;
	char		*tmp;
	char		*expanded;

	head = shell->instru;
	while (head && head->type == TEXT)
	{
		tmp = head->unquoted;
		expanded = expand(head->str, shell, 0, 0);
		if (!ft_strcmp(head->str, expanded))
			free(expanded);
		else
		{
			head->unquoted = expanded;
			free(tmp);
		}
		tmp = head->str;
		head->str = ft_unquote(head->unquoted, ft_strlen(head->unquoted));
		free(tmp);
		head = head->next;
	}
}

int	builtinunset(t_instru *instru, t_envar *head, t_shell *shell)
{
	int		i;
	char	*name;

	i = 1;
	if (!instru->next || instru->next->type != TEXT)
	{
		print_err("minishell: unset: not enough arguments\n");
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
	shell->exit_status = 0;
	return (i);
}
