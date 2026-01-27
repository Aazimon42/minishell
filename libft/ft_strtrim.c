/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:10:28 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/19 17:57:57 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char const *set, char to_find)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == to_find)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	if (!s1 || !set)
		return (0);
	i = 0;
	size = ft_strlen(s1);
	while (ft_inset(set, s1[i++]))
		size--;
	i = ft_strlen(s1) - 1;
	if (size > 0)
		while (ft_inset(set, s1[i--]))
			size--;
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (0);
	i = 0;
	j = -1;
	while (ft_inset(set, s1[i]))
		i++;
	while (++j < size)
		str[j] = s1[i + j];
	return (str);
}
