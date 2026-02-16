/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:18:39 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/17 00:22:16 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

double	vec_len(t_vec3 vec)
{
	return (sqrt(pow(vec.e[X], 2) + pow(vec.e[Y], 2) + pow(vec.e[Z], 2)));
}

t_vec3	vec_cross(t_vec3 first, t_vec3 second)
{
	t_vec3	res;

	res.e[X] = first.e[Y] * second.e[Z] - first.e[Z] * second.e[Y];
	res.e[Y] = first.e[Z] * second.e[X] - first.e[X] * second.e[Z];
	res.e[Z] = first.e[X] * second.e[Y] - first.e[Y] * second.e[X];
	return (res);
}

t_vec3	vec_normalize(t_vec3 vec)
{
	double	len;
	t_vec3	res;

	len = vec_length(vec);
	if (len < 1e-8)
	{
		res.e[X] = 0;
		res.e[Y] = 0;
		res.e[Z] = 0;
		return (res);
	}
	res.e[X] = vec.e[X] / len;
	res.e[Y] = vec.e[Y] / len;
	res.e[Z] = vec.e[Z] / len;
	return (res);
}
