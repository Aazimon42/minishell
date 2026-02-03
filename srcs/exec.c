/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:43:03 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/03 09:36:28 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	builtexec(t_instru *instru, t_envar *envhead)
{
	int	executed;

	executed = 0;
	if (!ft_strcmp(instru->str, "cd"))
		executed += builtincd(instru);
	if (!ft_strcmp(instru->str, "echo"))
		executed += builtinecho(instru);
	if (!ft_strcmp(instru->str, "pwd"))
		executed += builtinpwd(instru);
	if (!ft_strcmp(instru->str, "export"))
		executed += builtinexport(instru, envhead);
	if (!ft_strcmp(instru->str, "unset"))
		executed += builtinunset(instru, envhead);
	if (!ft_strcmp(instru->str, "env"))
		executed += builtinenv(envhead);
	/*if (!ft_strcmp(instru->str, "exit"))
		builtinexit(instru, envhead);*/
	return (executed);
}

void	execute(t_instru *instru, t_envar *envhead)
{
	int	i;

	while (instru)
	{
		i = builtexec(instru, envhead) + 1;
		while (i > 0)
		{
			if (instru)
				instru = instru->next;
			i--;
		}
	}
}
