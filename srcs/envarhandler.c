/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarhandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 08:03:35 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/07 08:04:24 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_evname(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	if (str[0] == '$')
		str++;
	while (str[i] && str[i] != ' ' && (ft_isalnum(str[i]) || str[i] == '?'))
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	j = 0;
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

static char	*get_evvalue(char *str, t_envar *envar)
{
	while (envar)
	{
		if (ft_strcmp(str, envar->name) == 0)
			return (envar->value);
		envar = envar->next;
	}
	return (NULL);
}

static void	replaceenvar(char **str, char *name, char *value, int pos)
{
	int		i[3];
	char	*result;

	if (!name)
		return ;
	if (!value)
		value = "";
	result = malloc(ft_strlen(*str) - ft_strlen(name) + ft_strlen(value) + 1);
	if (!result)
		return ;
	i[0] = 0;
	i[1] = 0;
	while (i[0] < pos)
		result[i[1]++] = (*str)[i[0]++];
	i[2] = 0;
	while (value[i[2]])
		result[i[1]++] = value[i[2]++];
	i[0] = pos + ft_strlen(name) + 1;
	while ((*str)[i[0]])
		result[i[1]++] = (*str)[i[0]++];
	result[i[1]] = '\0';
	free(*str);
	free(name);
	*str = result;
}

char	*expand(char *str, t_envar *envar, t_shell *shell)
{
	int		i;
	int		in_s;
	int		in_d;
	char	*res;
	char	*temp;

	i = 0;
	in_s = 0;
	in_d = 0;
	res = ft_strdup(str);
	while (res[i])
	{
		if (res[i] == '\'' && !in_d)
			in_s = !in_s;
		else if (res[i] == '"' && !in_s)
			in_d = !in_d;
		else if (res[i] == '$' && res[i + 1] && res[i + 1] != ' ' && !in_s)
		{
			temp = get_evname(&res[i]);
			if (res[i + 1] == '?')
				replaceenvar(&res, temp, ft_itoa(shell->exit_status), i);
			else
				replaceenvar(&res, temp, get_evvalue(temp, envar), i);
			i++;
		}
		i++;
	}
	return (res);
}

void	handle_envar(t_shell *shell)
{
	t_instru	*head;

	head = shell->instru;
	while (head && head->type == TEXT)
	{
		head->str = expand(head->str, shell->envhead, shell);
		free(head->unquoted);
		head->unquoted = ft_unquote(head->str, ft_strlen(head->str));
		head = head->next;
	}
}
