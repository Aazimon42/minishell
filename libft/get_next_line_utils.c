/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:55:06 by edi-maio          #+#    #+#             */
/*   Updated: 2026/01/29 04:14:05 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
	{
		str = ft_strdup(s2);
		return (str);
	}
	i = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
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

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(src) * sizeof (char) + 1);
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
	if (start > ft_strlen(s1))
		size = 0;
	else
		size = ft_strlen(s1) - start;
	if (size > len)
		size = len;
	subs = malloc(size + 1);
	if (!subs)
		return (0);
	i = 0;
	while (s1[start] && i < len)
		subs[i++] = s1[start++];
	subs[i] = '\0';
	free(s2);
	return (subs);
}

ssize_t	ft_strchr_gnl(const char *str, int c, ssize_t nb_read)
{
	int	i;

	if (!str)
		return (-1);
	if (nb_read == 0 && ft_strlen(str))
		return (ft_strlen(str) - 1);
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
