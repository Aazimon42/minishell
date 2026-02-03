/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:18:34 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/03 07:58:29 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(t_envar *head)
{
	int	len;

	while (head)
	{
		len = ft_strlen(head->value);
		printf("%s=", head->name);
		if (len == 0)
			printf("''\n");
		else if (head->value[0] == ' ' || head->value[len - 1] == ' ')
			printf("'%s'\n", head->value);
		head = head->next;
	}
}

void	replace_envar(t_envar *head, char *name, char *value)
{
	if (ft_strlen(value) == 0)
	{
		free(value);
		return ;
	}
	while (head)
	{
		if (!ft_strcmp(head->name, name))
		{
			free(head->value);
			head->value = value;
		}
		head = head->next;
	}
}

t_envar *delete_envar(t_envar *head, char *name)
{
    t_envar *tmp = head;
    t_envar *prev = NULL;

    while (tmp)
    {
        if (!ft_strcmp(tmp->name, name))
        {
            if (prev)
                prev->next = tmp->next;
            else
                head = tmp->next;
            free(tmp->name);
            free(tmp->value);
            free(tmp);
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return head;
}

int	builtinexport(t_instru *instru, t_envar *envar)
{
	int		i;
	char	*name;
	int		found;
	t_envar	*tmp;

	i = 1;
	if (!instru->next || instru->next->type != TEXT)
	{
		print_env(envar);
		return (i);
	}
	while (instru->next && instru->next->type == TEXT)
	{
		found = 0;
		tmp = envar;
		name = get_envar_name(instru->next->str);
		i += 1;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, name))
			{
				replace_envar(envar, name, get_envar_value(instru->next->str));
				found = 1;
			}
			tmp = tmp->next;
		}
		if (!found)
			add_envar(name, get_envar_value(instru->next->str), envar);
		instru = instru->next;
	}
	return (i);
}


