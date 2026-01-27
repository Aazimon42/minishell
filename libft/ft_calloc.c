/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:12:02 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/19 18:06:19 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (size == 0)
	{
		arr = malloc(0);
		if (!arr)
			return (0);
	}
	else if (nmemb * size / size != nmemb)
		return (0);
	else
	{
		arr = malloc(nmemb * size);
		if (arr == 0)
			return (0);
		ft_bzero(arr, size * nmemb);
	}
	return (arr);
}
