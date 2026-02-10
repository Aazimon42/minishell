/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:01 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/10 17:37:24 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

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
	char					*unquoted;
	int						type;
}		t_instru;

typedef	struct s_envar
{
	struct s_envar	*next;
	char			*name;
	char			*value;
}				t_envar;

t_instru	*init_instruction(t_instru *before, char *value, int size, int type);
t_instru	*slicer(char *str);
t_instru    *clear_instru(t_instru *head);
void		free2d(char **arr);
int			builtincd(t_instru *instru);
int			builtinecho(t_instru *instru);
int 		builtinpwd(void);
int 		builtinexport(t_instru *instru, t_envar *envhead);
void    	transformtilde(t_instru *instru);
void    	execute(t_instru *instru, t_envar *envhead);
t_envar 	*setup_envar(char **env);
void    	add_envar(char *name, char *value, t_envar *head);
t_envar 	*setup_envar(char **env);
int			ft_strcmp(const char *s1, const char *s2);
char		*get_envar_name(char *str);
char		*get_envar_value(char *str);
void		print_env(t_envar *head);
void		print_export(t_envar *head);
int			builtinunset(t_instru *instru, t_envar *head);
int			builtinenv(t_envar *head);
void		print_error(char *str);
void		builtinexit(t_instru *instru, t_envar *head);
char		*get_var(t_envar *head, char *name, int i);
void		handle_envar(t_instru *head, t_envar *envar);
char	*ft_unquote(char *s1, int size);

#endif
