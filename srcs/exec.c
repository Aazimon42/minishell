/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:43:03 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/26 20:11:23 by edi-maio         ###   ########.fr       */
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
		cmd = ft_strjoin(cmd, " ");
		free(tmp);
		if (!cmd)
			return (0);
		tmp = cmd;
		cmd = ft_strjoin(cmd, instru->next->str);
		free(tmp);
		if (!cmd)
			return (0);
		instru = instru->next;
	}
	return (cmd);
}

void	executeve(t_instru *instru, t_envar *envhead)
{
	char	**split_cmd;
	char	*cmd;
	char	*path;
	char	**env;

	cmd = ft_join_instru(instru);
	env = split_env(envhead);
	split_cmd = ft_split(cmd, ' ');
	if (access(split_cmd[0], F_OK | X_OK) == 0)
		path = split_cmd[0];
	else
		path = get_cmd(split_cmd[0], env);
	free(cmd);
	if (!path || execve(path, split_cmd, env) == -1)
	{
		if (path)
			free(path);
		free2d(env);
		return ;
	}
}

static int	builtexec(t_instru *instru, t_envar *envhead)
{
	int		executed;
	pid_t	pid1;

	executed = 0;
	if (!ft_strcmp(instru->str, "cd"))
		executed += builtincd(instru);
	else if (!ft_strcmp(instru->str, "echo"))
		executed += builtinecho(instru);
	else if (!ft_strcmp(instru->str, "pwd"))
		executed += builtinpwd();
	else if (!ft_strcmp(instru->str, "export"))
		executed += builtinexport(instru, envhead);
	else if (!ft_strcmp(instru->str, "unset"))
		executed += builtinunset(instru, envhead);
	else if (!ft_strcmp(instru->str, "env"))
		executed += builtinenv(envhead);
	else if (!ft_strcmp(instru->str, "exit"))
		builtinexit(instru, envhead);
	else
	{
		pid1 = fork();
		if (pid1 == 0)
			executeve(instru, envhead);
		waitpid(pid1, NULL, 0);
		if (pid1 == 0)
			exit(0);
		executed = 1;
	}
	return (executed);
}

void	execute(t_instru *instru, t_envar *envhead)
{
	int	i;
	int	save_stdout;
	int	save_stdin;

	while (instru)
	{
		i = 0;
		save_stdin = -1;
		save_stdout = -1;
		handle_envar(instru, envhead);
		if (instru->next && instru->next->type == SEPARATOR
			&& instru->next->str[0] == '<' && instru->next->str[1] == '<')
			save_stdin = handle_heredoc(instru->next);
		if (instru->next && next_sep_is_redirect(instru->next))
		{
			save_stdout = dup(STDOUT_FILENO);
			if (!handle_redirect(instru->next))
			{
				printf("Minishell: %s: Permission denied\n", instru->next->next->next->str);
				return ;
			}
		}
		i += builtexec(instru, envhead) + 1;
		if (save_stdin != -1)
		{
			dup2(save_stdin, STDIN_FILENO);
			close(save_stdin);
		}
		if (save_stdout != -1)
		{
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdout);
		}
		while (i > 0 && instru)
		{
			instru = instru->next;
			i--;
		}
	}
}
