/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:58:11 by aoperacz          #+#    #+#             */
/*   Updated: 2024/11/21 00:27:30 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	int				i;
	char			res[13];

	i = 0;
	ft_bzero(res, 13);
	if (n == 0)
		res[i++] = '0';
	if (n < 0)
		num = (unsigned int)(-n);
	else
		num = (unsigned int)(n);
	while (num > 0)
	{
		res[i] = num % 10 + '0';
		num = num / 10;
		i++;
	}
	if (n < 0)
		res[i++] = '-';
	while (--i >= 0)
		write(fd, &res[i], 1);
}

// int	main(void)
// {
// 	ft_putnbr_fd(0, 1);
// 	return (0);
// }
