/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:20:30 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/01 22:44:47 by edi-maio         ###   ########.fr       */
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

char	*ft_strcat(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
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
		temp = ft_strcat(possible[i], "/");
		path = ft_strcat(temp, cmd);
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
