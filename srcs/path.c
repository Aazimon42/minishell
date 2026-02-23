/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:20:30 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/23 18:15:51 by edi-maio         ###   ########.fr       */
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

char	*get_cmd(char *cmd, char **env)
{
	char	*path;
	char	**possible;
	int		i;
	char	*temp;

	path = get_path(env);
	if (!path)
		return (NULL);
	possible = ft_split(path + 5, ':');
	i = 0;
	while (possible[i])
	{
		temp = ft_strjoin(possible[i], "/");
		if (!temp)
		{
			free2d(possible);
			return (0);
		}
		path = ft_strjoin(temp, cmd);
		if (!path)
		{
			free2d(possible);
			free(temp);
			return (0);
		}
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free2d(possible);
			return (path);
		}
		free(path);
		i++;
	}
	free2d(possible);
	return (NULL);
}
