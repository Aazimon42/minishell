/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:47 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/04 07:47:18 by malebrun         ###   ########.fr       */
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
	t_envar		*envhead;

	if (ac != 1)
		return (1);
	(void)av;
	envhead = setup_envar(env);
	instru = NULL;
	while (1)
	{
		str = readline(rainbow_prompt());
		if (!str[0])
			continue ;
		add_history(str);
		instru = slicer(str);
		/*while (instru)
		{
			printf("Type:%d, Value:%s\n", instru->type, instru->str);
			instru = instru->next;
		}*/
		execute(instru, envhead);
		instru = clear_instru(instru);
	}
}
