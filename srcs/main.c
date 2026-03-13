/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:47 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/13 01:52:43 by edi-maio         ###   ########.fr       */
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

static int	minishell_logic(t_shell *shell, char *str)
{
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = readline(rainbow_prompt());
		if (!str)
		{
			free_instru(shell->instru);
			free_envar(shell->envhead);
			return (0);
		}
		if (g_exit_status != 0)
			shell->exit_status = g_exit_status;
		g_exit_status = 0;
		if (!str[0])
			continue ;
		add_history(str);
		shell->instru = slicer(str);
		execute(shell);
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
	shell.envhead = setup_envar(env);
	shell.instru = NULL;
	shell.exit_status = 0;
	shell.save_stdin = -1;
	shell.save_stdout = -1;
	minishell_logic(&shell, str);
}
