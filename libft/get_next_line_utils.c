/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:55:06 by edi-maio          #+#    #+#             */
/*   Updated: 2026/03/22 17:28:12 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	slen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
	{
		str = ft_strdup_gnl(s2);
		return (str);
	}
	i = 0;
	str = malloc(slen(s1) + slen(s2) + 1);
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[0])
	{
		str[i++] = s2[0];
		s2++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup_gnl(const char *src)
{
	char	*dest;
	int		i;

	dest = malloc(slen(src) * sizeof (char) + 1);
	if (!dest)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr_gnl(char *s1, char *s2, size_t start, size_t len)
{
	char	*subs;
	size_t	size;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	if (start > slen(s1))
		size = 0;
	else
		size = slen(s1) - start;
	if (size > len)
		size = len;
	subs = malloc(size + 1);
	if (!subs)
		return (0);
	i = 0;
	while (s1[start] && i < len)
		subs[i++] = s1[start++];
	subs[i] = '\0';
	if (i > 0 && subs[slen(subs) - 1] == '\n')
		subs[i - 1] = '\0';
	free(s2);
	return (subs);
}

ssize_t	ft_strchr_gnl(const char *str, int c, ssize_t nb_read)
{
	int	i;

	if (!str)
		return (-1);
	if (nb_read == 0 && slen(str))
		return (slen(str) - 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (str[i] == (unsigned char)c)
		return (i);
	return (-1);
}
