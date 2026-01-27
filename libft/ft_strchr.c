/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:47:30 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/19 18:35:52 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	while (str[0])
	{
		if (str[0] == (unsigned char)c)
			return ((char *) str);
		str++;
	}
	if (str[0] == (unsigned char)c)
		return ((char *) str);
	return (0);
}
