/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:18:34 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/07 08:31:02 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_envar(t_envar *head, char *name, char *value)
{
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

int	builtinexport(t_instru *instru, t_envar *envar, t_shell *shell)
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
		tmp = envar;
		name = get_envar_name(instru->next->unquoted);
		if (!is_fullalnum(name))
		{
			print_error("minishell: export: '");
			print_error(name);
			print_error("': not a valid identifier\n");
			shell->exit_status = 1;
			return (i);
		}
		i += 1;
		found = find_and_replace_env(tmp, name, instru);
		if (!found)
			add_envar(name, get_envar_value(instru->next->unquoted), envar);
		instru = instru->next;
	}
	shell->exit_status = 0;
	return (i);
}

int	builtinenv(t_envar *head, t_shell *shell)
{
	print_env(head);
	shell->exit_status = 0;
	return (1);
}

int	builtinunset(t_instru *instru, t_envar *head, t_shell *shell)
{
	int		i;
	char	*name;

	i = 1;
	if (!instru->next || instru->next->type != TEXT)
	{
		print_error("minishell: unset: not enough arguments\n");
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
