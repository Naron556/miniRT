/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:27:51 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/14 18:24:08 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long		i;
	const unsigned char	*str;
	unsigned char		*des;

	str = src;
	des = dest;
	if (str == NULL && dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		des[i] = str[i];
		i++;
	}
	return (dest);
}
