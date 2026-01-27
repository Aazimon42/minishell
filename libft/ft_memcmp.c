/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:45:16 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/16 16:17:56 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		val;

	i = 0;
	val = 0;
	while (val == 0 && i < n)
	{
		val = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		i++;
	}
	return (val);
}
