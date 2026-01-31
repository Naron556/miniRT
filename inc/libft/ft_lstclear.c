/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:50:16 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/23 02:10:15 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temporary_node;

	if (!lst || !del)
	{
		return ;
	}
	while (*lst != NULL)
	{
		temporary_node = *lst;
		*lst = temporary_node->next;
		del(temporary_node->content);
		free(temporary_node);
	}
	*lst = NULL;
}
