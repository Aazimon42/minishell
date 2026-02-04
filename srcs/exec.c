/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:43:03 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/04 15:03:47 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static void	replace_var(t_instru *instru, t_envar *head)
{
	int		i;
	int		j;
	char	*value;

	while (instru && instru->type == TEXT)
	{
		i = 0;
		while (instru->str[i])
		{
			j = 0;
			if (instru->str[i] == '\'')
			{
				while (instru->str[i] && instru->str[i] != '\'')
					i++;
				if (instru->str[i] == '\'')
					i++;
			}
			if (instru->str[i] == '$')
			{
				j = 0;
				while (instru->str[i] && instru->str[i] != ' ')
				{
					i++;
					j++;
				}
				value = get_var(head, instru->str + i, j);
			}
		}
		instru = instru->next;
	}
}*/

static int	builtexec(t_instru *instru, t_envar *envhead)
{
	int	executed;

	executed = 0;
	if (!ft_strcmp(instru->str, "cd"))
		executed += builtincd(instru);
	if (!ft_strcmp(instru->str, "echo"))
		executed += builtinecho(instru);
	if (!ft_strcmp(instru->str, "pwd"))
		executed += builtinpwd();
	if (!ft_strcmp(instru->str, "export"))
		executed += builtinexport(instru, envhead);
	if (!ft_strcmp(instru->str, "unset"))
		executed += builtinunset(instru, envhead);
	if (!ft_strcmp(instru->str, "env"))
		executed += builtinenv(envhead);
	if (!ft_strcmp(instru->str, "exit"))
		builtinexit(instru, envhead);
	return (executed);
}

void	execute(t_instru *instru, t_envar *envhead)
{
	int	i;

	while (instru)
	{
		handle_envar(instru, envhead);
		i = builtexec(instru, envhead) + 1;
		while (i > 0)
		{
			if (instru)
				instru = instru->next;
			i--;
		}
	}
}
