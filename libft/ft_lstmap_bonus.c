/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:39:48 by edi-maio          #+#    #+#             */
/*   Updated: 2025/10/20 16:43:16 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*tmp;
	void	*data;

	if (!lst || !f || !del)
		return (0);
	map = NULL;
	while (lst)
	{
		data = f(lst->content);
		tmp = ft_lstnew(data);
		if (!tmp || !data)
		{
			del(data);
			ft_lstdelone(tmp, del);
			ft_lstclear(&map, del);
			return (0);
		}
		ft_lstadd_back(&map, tmp);
		lst = lst->next;
	}
	return (map);
}
