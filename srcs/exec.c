/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:43:03 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/12 15:38:03 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_instru(t_instru *instru)
{
	char	*tmp;
	char	*cmd;

	cmd = ft_strdup(instru->str);
	if (!cmd)
		return (0);
	while (instru->next && instru->next->type == TEXT)
	{
		tmp = cmd;
		cmd = ft_strjoin(cmd, instru->next->str);
		free(tmp);
		if (!cmd)
			return (0);
		tmp = cmd;
		cmd = ft_strjoin(cmd, " ");
		free(tmp);
		if (!cmd)
			return (0);
		instru = instru->next;
	}
	return (cmd);
}

void	executeve(t_instru *instru, char **env)
{
	char	**split_cmd;
	char	*cmd;
	char	*path;

	cmd = ft_join_instru(instru);
	split_cmd = ft_split(cmd, ' ');
	if (access(cmd, F_OK | X_OK) == 0)
		path = split_cmd[0];
	else
		path = get_cmd(split_cmd[0], env);
	free(cmd);
	if (!path)
	{
		free(path);
		free2d(split_cmd);
		exit(127);
	}
	if (execve(path, split_cmd, env) == -1)
	{
		free(path);
		free2d(split_cmd);
		return ;
	}
}

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
	else
		executeve(instru, envhead);
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
