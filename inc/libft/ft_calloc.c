/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:26:37 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/14 18:08:12 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tsize;
	void	*arr;

	tsize = nmemb * size;
	arr = malloc(tsize);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, tsize);
	return (arr);
}
