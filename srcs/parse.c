/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 05:02:40 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/03 08:39:40 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_forbidenchar(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (1);
	if (ft_strlen(str) > 1 && str[0] == '&' && str[1] == '&')
		return (1);
	return (0);
}

static int	get_end_instru(char *str)
{
	int		i;
	char	quote;

	i = 0;
	if ((str[0] == '&' && str[1] == '&') || (str[0] == '|' && str[1] == '|')
		|| (str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	if (str[0] == '<' || str[0] == '>' || str[0] == '|')
		return (1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		if (str[i] == ' ' || is_forbidenchar(&str[i]))
			break ;
		i++;
	}
	return (i);
}

static int	gtype(char *str, int len)
{
	if (len == 2 && ((str[0] == '&' || str[0] == '<' || str[0] == '>' || str[0] == '|') && str[0] == str[1]))
		return (SEPARATOR);
	if (len == 1 && ((str[0] == '<') || str[0] == '>'))
		return (SEPARATOR);
	if (len == 1 && str[0] == '|')
		return (PIPE);
	return (TEXT);
}

t_instru	*slicer(char *str)
{
	int			i;
	int			len;
	t_instru	*head;
	t_instru	*temp;
	t_instru	*instru;

	if (ft_strlen(str) == 0)
		return (NULL);
	i = 0;
	len = get_end_instru(str + i);
	head = init_instruction(NULL, str + i, len, gtype(str + i, len));
	instru = head;
	i += len;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		len = get_end_instru(str + i);
		temp = init_instruction(instru, str + i, len, gtype(str + i, len));
		instru = temp;
		i += len;
	}
	return (head);
}
