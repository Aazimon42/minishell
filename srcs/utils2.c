/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:56:07 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/15 21:03:19 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

static int	env_size(t_envar *envhead)
{
	int	count;

	count = 0;
	while (envhead)
	{
		count++;
		envhead = envhead->next;
	}
	return (count);
}

char	**split_env(t_envar *envhead)
{
	char	**env;
	int		count;
	int		i;

	count = env_size(envhead);
	env = malloc(sizeof(char *) * count);
	if (!env)
		return (0);
	i = 0;
	while (i < count)
	{
		env[i] = malloc(sizeof(char) * (ft_strlen(envhead->name) + ft_strlen(envhead->value) + 2));
		if (!env[i])
		{
			free2d(env);
			return (0);
		}
		ft_strcpy(env[i], envhead->name);
		ft_strcat(env[i], "=");
		ft_strcat(env[i], envhead->value);
		envhead = envhead->next;
		i++;
	}
	return (env);
}
