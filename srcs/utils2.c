/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:15:33 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/12 23:19:32 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	formatenv(char *env, t_envar *envhead)
{
	ft_strcpy(env, envhead->name);
	ft_strcat(env, "=");
	ft_strcat(env, envhead->value);
}

int	find_and_replace_env(t_envar *tmp, char *name, t_instru *instru)
{
	int	found;

	found = 0;
	while (tmp && !found)
	{
		if (name && tmp->name && !ft_strcmp(tmp->name, name)
			&& (instru->next->str[ft_strlen(name)] == '='
				|| instru->next->str[ft_strlen(name)] == '\0'))
		{
			replace_envar(tmp, name,
				get_envar_value(instru->next->str));
			found = 1;
		}
		tmp = tmp->next;
	}
	return (found);
}

void	increment_double_int(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

int	is_fullalnum(char *str)
{
	if (*str && !ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(str[0]) && str[0] != '_')
			return (0);
		str++;
	}
	return (1);
}

int	handle_error_builtinexport(char *str, t_shell *shell)
{
	if (!is_fullalnum(str))
	{
		print_err("minishell: export : '");
		print_err(str);
		print_err("': not a valide identifier\n");
		shell->exit_status = 1;
		return (0);
	}
	return (1);
}
