/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malebrun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:21:12 by malebrun          #+#    #+#             */
/*   Updated: 2026/03/10 13:27:55 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_error_builtinexport(char *str, t_shell *shell)
{
	if (!is_fullalnum(str))
	{
		print_error("minishell: export : '");
		print_error(str);
		print_error("': not a valide identifier\n");
		shell->exit_status = 1;
		return (0);
	}
	return (1);
}
