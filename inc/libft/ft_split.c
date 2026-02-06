/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:17:02 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/23 02:32:20 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	amount_of_str(char const *s, char c)
{
	int	res;

	res = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res++;
			while (*s && *s != c)
				s++;
		}
	}
	return (res);
}

int	check_free(char **res, int i)
{
	if (res[i] == NULL)
	{
		while (i >= 0)
		{
			free(res[i]);
			i--;
		}
		free(res);
		return (1);
	}
	return (0);
}

char	**mallocations(const char *s, int strs, char **res, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s && i < strs)
	{
		while (*s != '\0' && *s == c)
			s++;
		while (s[j] != '\0' && s[j] != c)
			j++;
		if (j != 0)
		{
			res[i] = (char *)malloc((j + 1) * sizeof(char));
			if (check_free(res, i) == 1)
				return (NULL);
			res[i] = ft_memcpy(res[i], s, j);
			res[i][j] = '\0';
			s = s + j ;
			j = 0;
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		strs;

	strs = amount_of_str(s, c);
	res = (char **)malloc((strs + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (mallocations(s, strs, res, c));
}
