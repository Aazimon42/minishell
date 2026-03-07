/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:20:30 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/07 03:17:29 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

static char	*get_cmd_logic(char *path, char **possible, int i, char *cmd)
{
	char	*temp;

	while (possible[i])
	{
		temp = ft_strjoin(possible[i], "/");
		if (!temp)
		{
			return (NULL);
		}
		path = ft_strjoin(temp, cmd);
		if (!path)
		{
			free(temp);
			return (NULL);
		}
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_cmd(char *cmd, char **env)
{
	char	*path;
	char	**possible;
	int		i;
	char	*result;

	path = get_path(env);
	if (!path)
		return (NULL);
	possible = ft_split(path + 5, ':');
	i = 0;
	result = get_cmd_logic(path, possible, i, cmd);
	free2d(possible);
	if (result)
		return (result);
	return (NULL);
}
