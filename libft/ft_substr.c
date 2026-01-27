/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:41:08 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/23 17:44:58 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	size;
	size_t	i;

	if (!s)
		return (0);
	if (start > (unsigned int)ft_strlen(s))
		size = 0;
	else
		size = ft_strlen(s) - start;
	if (size > len)
		size = len;
	subs = malloc(size + 1);
	if (!subs)
		return (0);
	i = 0;
	while (i < size)
	{
		subs[i] = s[start];
		i++;
		start++;
	}
	subs[i] = 0;
	return (subs);
}
