/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:32:53 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/03 09:33:43 by edi-maio         ###   ########.fr       */
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
			if (!last_printed || strcmp(tmp->name, last_printed) > 0)
			{
				if (!min || (min && strcmp(tmp->name, min->name) < 0))
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
