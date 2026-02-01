/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:01 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/01 22:45:49 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RED "\033[91m"
# define ORANGE "\033[93m"
# define YELLOW "\033[93m"
# define GREEN "\033[92m"
# define CYAN "\001\033[36m\002"
# define BLUE "\033[94m"
# define INDIGO "\033[95m"
# define VIOLET "\033[95m"
# define RESET "\033[0m"

# define TEXT 1
# define SEPARATOR 2
# define PIPE 3

typedef struct s_instruction
{
	struct s_instruction	*pre;
	struct s_instruction	*next;
	char					*str;
	int						type;
}		t_instru;

t_instru	*init_instruction(t_instru *before, char *value, int size, int type);
t_instru	*slicer(char *str);
t_instru    *clear_instru(t_instru *head);
void		free2d(char **arr);

#endif
