/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:45:45 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/15 21:02:32 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static void	ft_fill_str(char *str, int n, int count)
{
	if (n / 10 != 0)
		ft_fill_str(str, n / 10, count - 1);
	if (n > 0)
		str[count - 1] = n % 10 + 48;
	else
		str[count - 1] = -(n % 10) + 48;
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	count = ft_count_digits(n);
	str = malloc(count + 1);
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
	}
	if (n == 0)
		str[0] = '0';
	ft_fill_str(str, n, count);
	str[count] = 0;
	return (str);
}
