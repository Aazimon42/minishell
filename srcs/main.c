/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:47 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/10 13:39:57 by malebrun         ###   ########.fr       */
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

static void	init_shell(t_shell *shell, char **env)
{
	shell->envhead = setup_envar(env);
	shell->instru = NULL;
	shell->exit_status = 0;
}

static int	minishell_logic(t_shell *shell, char *str)
{
	while (1)
	{
		signal(SIGINT, handle_sigint);
		str = readline(rainbow_prompt());
		if (!str)
		{
			free_instru(shell->instru);
			free_envar(shell->envhead);
			return (0);
		}
		if (!str[0])
			continue ;
		add_history(str);
		shell->instru = slicer(str);
		g_exit_status = -1;
		execute(shell);
		if (shell->exit_status == -1)
			shell->exit_status = g_exit_status;
		free_instru(shell->instru);
	}
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_shell		shell;

	if (ac != 1)
		return (1);
	(void)av;
	str = NULL;
	init_shell(&shell, env);
	minishell_logic(&shell, str);
}
