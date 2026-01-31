/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 01:20:02 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/23 02:31:03 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new_guy;

	res = NULL;
	if (!f || !lst || !del)
		return (NULL);
	while (lst)
	{
		new_guy = (t_list *)malloc(sizeof(t_list));
		if (!new_guy)
		{
			ft_lstclear(&lst, (*del));
			return (NULL);
		}
		new_guy->content = f(lst->content);
		new_guy->next = NULL;
		ft_lstadd_back(&res, new_guy);
		lst = lst->next;
	}
	return (res);
}
