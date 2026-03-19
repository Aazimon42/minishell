/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:32:53 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/19 18:46:44 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_wquote(t_envar *head)
{
	int	len;

	len = ft_strlen(head->value);
	printf("%s=", head->name);
	if (len == 0)
		printf("''\n");
	else if (head->value[0] == ' ' || head->value[len - 1] == ' ')
		printf("'%s'\n", head->value);
	else
		printf("%s\n", head->value);
}

void	print_export(t_envar *head)
{
	char	*last_printed;
	t_envar	*min;
	t_envar	*tmp;

	last_printed = NULL;
	while (1)
	{
		tmp = head;
		min = NULL;
		while (tmp)
		{
			if (!last_printed || ft_strcmp(tmp->name, last_printed) > 0)
			{
				if (!min || (min && ft_strcmp(tmp->name, min->name) < 0))
					min = tmp;
			}
			tmp = tmp->next;
		}
		if (!min)
			break ;
		print_wquote(min);
		last_printed = min->name;
	}
}

void	print_env(t_envar *head)
{
	while (head)
	{
		if (head->value[0] != '\0')
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
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
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (0);
	i = 0;
	while (i < count)
	{
		env[i] = malloc(sizeof(char) * (ft_strlen(envhead->name)
					+ ft_strlen(envhead->value) + 2));
		if (!env[i])
		{
			env[i] = NULL;
			free2d(env);
			return (0);
		}
		formatenv(env[i], envhead);
		envhead = envhead->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
