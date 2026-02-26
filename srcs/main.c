/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:47 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/26 18:30:51 by malebrun         ###   ########.fr       */
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
		execute(instru, envhead);
		free_instru(instru);
	}
}
