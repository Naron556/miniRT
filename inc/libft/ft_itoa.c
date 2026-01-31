/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:09:38 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/20 18:00:01 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	c_count(int n)
{
	int	len;
	int	num;

	num = n;
	len = 0;
	if (n <= 0)
		len = 1;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*conversion(unsigned int n, char *res, int len)
{
	len--;
	if (res[0] == '-')
	{
		while (len > 0 && n != 0)
		{
			res[len] = n % 10 + '0';
			n = n / 10;
			len--;
		}
	}
	else
	{
		while (len >= 0)
		{
			res[len] = n % 10 + '0';
			n = n / 10;
			len--;
		}
	}
	return (res);
}

char	*memory_allocation(int n, int len)
{
	char	*res;

	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (n < 0)
		res[0] = '-';
	res[len] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	number;

	len = c_count(n);
	if (n < 0)
		number = (unsigned int)(-n);
	else
		number = (unsigned int)(n);
	res = memory_allocation(n, len);
	if (!res)
		return (NULL);
	res = conversion(number, res, len);
	return (res);
}
