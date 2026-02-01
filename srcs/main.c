/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:47 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/01 19:54:35 by malebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_rainbow(char *str)
{
	static char	*colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};
	int			len;
	int			i;
	int			color;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		color = i % 7;
		write(1, colors[color], ft_strlen(colors[color]));
		write(1, &str[i], 1);
		write(1, RESET, ft_strlen(RESET));
		i++;
	}
}

int	main(int ac, char **av)
{
	char		*str;
	t_instru	*instru;

	if (ac != 1)
		return (1);
	(void)av;
	instru = NULL;
	while (1)
	{
		print_rainbow("Minishell $> ");
		str = get_next_line(0);
		if (str)
			instru = slicer(str);
		while (instru)
		{
			printf("value : %s, type : %d\n", instru->str, instru->type);
			instru = instru->next;
		}
		instru = clear_instru(instru);
	}
	return (0);
}
