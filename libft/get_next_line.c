/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:54:52 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/20 17:36:02 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_all(char **str, char **line)
{
	free(*line);
	*line = NULL;
	free(*str);
	*str = NULL;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	ssize_t		code;
	ssize_t		nb_read;

	nb_read = 1;
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (0);
	code = ft_strchr_gnl(str, '\n', 1);
	while (code == -1 && nb_read > 0)
	{
		nb_read = read(fd, line, BUFFER_SIZE);
		if (nb_read > 0)
		{
			line[nb_read] = '\0';
			str = ft_strjoin_gnl(str, line);
		}
		code = ft_strchr_gnl(str, '\n', nb_read);
	}
	if (code == -1 && nb_read <= 0)
		return (free_all(&str, &line));
	line = ft_substr_gnl(str, line, 0, code + 1);
	str = ft_substr_gnl(str, str, code + 1, slen(str) - code + 1);
	return (line);
}
