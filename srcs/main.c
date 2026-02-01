/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:47 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/01 22:47:00 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*rainbow_prompt(void)
{
	return (
		RED "M"
		ORANGE "i"
		YELLOW "n"
		GREEN "i"
		CYAN "s"
		BLUE "h"
		INDIGO "e"
		VIOLET "l"
		RED "l"
		ORANGE " "
		YELLOW "$"
		GREEN ">"
		CYAN " "
		RESET
	);
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_instru	*instru;

	if (ac != 1)
		return (1);
	(void)av;
	instru = NULL;
	while (1)
	{
		str = readline(rainbow_prompt());
		if (!str[0])
			continue ;
		add_history(str);
		instru = slicer(str);
		while (instru)
		{
			printf("value : %s, type : %d\n", instru->str, instru->type);
			instru = instru->next;
		}
		instru = clear_instru(instru);
	}
}
