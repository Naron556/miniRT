/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:32:58 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/13 14:31:13 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = ft_strlen(dest);
	s = ft_strlen(src);
	i = 0;
	if (d < size - 1 && size > 0)
	{
		while (d + i < size - 1 && src[i] != '\0')
		{
			dest[d + i] = src[i];
			i++;
		}
		dest[d + i] = '\0';
	}
	if (d >= size)
		d = size;
	return (d + s);
}
