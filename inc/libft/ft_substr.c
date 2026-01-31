/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:54:57 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/18 21:28:12 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned long	i;
	char			*res;

	i = 0;
	if ((unsigned long)(start) >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - (unsigned long)start))
		len = ft_strlen(s) - (unsigned long)start;
	res = (char *)malloc((len + 1) * (sizeof(char)));
	if (res == NULL)
		return (NULL);
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
