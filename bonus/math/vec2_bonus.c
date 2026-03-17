/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:18:39 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/15 17:14:27 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

double	vec_len(t_vec3 vec)
{
	return (sqrt(pow(vec.e[x], 2) + pow(vec.e[y], 2) + pow(vec.e[z], 2)));
}

t_vec3	vec_cross(t_vec3 first, t_vec3 second)
{
	t_vec3	res;

	res.e[x] = first.e[y] * second.e[z] - first.e[z] * second.e[y];
	res.e[y] = first.e[z] * second.e[x] - first.e[x] * second.e[z];
	res.e[z] = first.e[x] * second.e[y] - first.e[y] * second.e[x];
	return (res);
}

t_vec3	vec_normalize(t_vec3 vec)
{
	double	len;
	t_vec3	res;

	len = vec_len(vec);
	if (len < 1e-8)
	{
		res.e[x] = 0;
		res.e[y] = 0;
		res.e[z] = 0;
		return (res);
	}
	res.e[x] = vec.e[x] / len;
	res.e[y] = vec.e[y] / len;
	res.e[z] = vec.e[z] / len;
	return (res);
}
