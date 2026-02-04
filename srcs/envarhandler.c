/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarhandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 08:03:35 by malebrun          #+#    #+#             */
/*   Updated: 2026/02/04 15:46:10 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_evname(char *str)
{
	int		i;
	char	*result;
	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	result = malloc(sizeof(char) * i);
	if (!result)
		return (NULL);
	i = 1;
	while (str[i] && str[i] != ' ')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*get_evvalue(char *str, t_envar *envar)
{
	while (envar)
	{
		if (strcmp(str, envar->name) == 0)
			return (envar->value);
		envar = envar->next;
	}
	return (NULL);
}

static void replaceenvar(t_instru *head, char *name, char *value, unsigned long nbdollar)
{
	int i;
	unsigned long j;
	int k;
	char *result;

	k = 0;
	j = 0;
	i = 0;
	if (!name || !value)
		return ;
	result = malloc(ft_strlen(head->str) - ft_strlen(name) + ft_strlen(value) + 1);
	if (!result)
		return ;
	while (j != nbdollar && head->str[i])
	{
		while (head->str[i] && head->str[i] != '$')
			i++;
		result[i] = head->str[i];
		i++;
		j++;
	}
	j = 0;
	i--;
	while (j < ft_strlen(value))
	{
		result[i + j] = value[j];
		j++;
	}
	j = i + j;
	i = i + ft_strlen(name);
	while(head->str[i])
	{
		result[j] = head->str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	free(head->str);
	free(name);
	head->str = result;
}
static void	expand(t_instru *head, t_envar *envar)
{
	int	i;
	int inbadquote;
	unsigned long	nbdollar;
	char *temp;

	inbadquote = 0;
	i = 0;
	nbdollar = 0;
	while (head->str[i])
	{
		fflush(stdout);
		if (head->str[i] == '$')
			nbdollar++;
		fflush(stdout);
		if ((i == 0 && head->str[i] == '\"') || (i > 0 && head->str[i] == '\"' && head->str[i - 1] != '\\'))
			inbadquote++;
		fflush(stdout);
		if ((head->str[i] == '$' && head->str[i + 1] && head->str[i + 1] != ' ') && inbadquote % 2 == 0)
		{
			temp = get_evname(&head->str[i]);
			printf("4");
			fflush(stdout);
			replaceenvar(head, temp,get_evvalue(temp, envar), nbdollar);
			printf("5");
			fflush(stdout);
			nbdollar = 0;
			inbadquote = 0;
			i = 0;
		} else {
			i++;
		}
	}
}

void	handle_envar(t_instru *head, t_envar *envar)
{
	while (head && head->type == TEXT)
	{
		expand(head, envar);
		head = head->next;
	}
}
