/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:03:07 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/15 19:47:16 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		val;

	i = 0;
	val = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && val == 0 && i < n)
	{
		val = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (val);
}
