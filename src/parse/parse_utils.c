/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:13:28 by yamohamm          #+#    #+#             */
/*   Updated: 2026/02/16 20:32:33 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int count_tokens(char **tokens)
{
	int i;
	i = 0;
	while(tokens[i])
	i++;
	return(i);
}

double	ft_atofraction(const char **str)
{
	double	result;
	double	power;

	result = 0.0;
	power = 1.0;
	(*str)++;
	while (ft_isdigit(**str))
	{
		result = result * 10.0 + (**str - '0');
		power *= 10.0;
		(*str)++;
	}
	return (result / power);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	int		f;

	result = 0.0;
	sign = 1.0;
	f = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	result = ft_atodigit(&str);
	if (*str == '.')
	{
		f = 1;
		result += ft_atofraction(&str);
	}
	return (result * sign);
}