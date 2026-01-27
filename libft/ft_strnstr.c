/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:18:09 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/23 18:09:20 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = ft_strlen(to_find);
	if (size == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		while (to_find[j] && str[i + j] == to_find[j] && i + j < len)
		{
			j++;
			if (j == size)
				return ((char *)&str[i]);
		}
		j = 0;
		i++;
	}
	return (0);
}
