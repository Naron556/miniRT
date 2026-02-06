/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:25:55 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/21 00:13:33 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	if (!*little)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		while (little[j] == big[i + j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return ((char *)((big + i)));
		else
		{
			j = 0;
			i++;
		}
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	haystack[30] = "aaabcabcd";
// 	char	needle[10] = "aabc";
// 	char	*empty;

// 	empty = (char *)"";
// 	printf("%s", ft_strnstr(empty, "", -1));
// 	return (0);
// }
