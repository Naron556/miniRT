// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parse_utils.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/02/16 20:13:28 by yamohamm          #+#    #+#             */
// /*   Updated: 2026/02/22 18:20:15 by yamohamm         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "miniRT.h"

// int count_tokens(char **tokens)
// {
// 	int i;
// 	i = 0;
// 	while(tokens[i])
// 	i++;
// 	return(i);
// }

// double	ft_atofraction(const char **str)
// {
// 	double	result;
// 	double	power;

// 	result = 0.0;
// 	power = 1.0;
// 	(*str)++;
// 	while (ft_isdigit(**str))
// 	{
// 		result = result * 10.0 + (**str - '0');
// 		power *= 10.0;
// 		(*str)++;
// 	}
// 	return (result / power);
// }

// double	ft_atof(const char *str)
// {
// 	double	result;
// 	double	sign;
// 	int		f;

// 	result = 0.0;
// 	sign = 1.0;
// 	f = 0;
// 	while (ft_isspace(*str))
// 		str++;
// 	if (*str == '-')
// 	{
// 		sign = -1.0;
// 		str++;
// 	}
// 	else if (*str == '+')
// 	{
// 		str++;
// 	}
// 	result = ft_atodigit(&str);
// 	if (*str == '.')
// 	{
// 		f = 1;
// 		result += ft_atofraction(&str);
// 	}
// 	return (result * sign);
// }

// t_vec3 parse_vec3(char *str)
// {
// 	t_vec3 vec;
// 	char **parts;

// 	parts = ft_split(str, ",");
// 	if(count_tokens(parts) !=3)
// 	{
// 		printf("Error\ninvalid vector format: %s\n, str");
// 		free_tokens(parts);
// 		exit(1);
// 	}
// 	vec.e[0] = ft_atof(parts[0]);
// 	vec.e[1] = ft_atof(parts[1]);
// 	vec.e[2] = ft_atof(parts[2]);
// 	free_tokens(parts);
// 	return(vec);
// }