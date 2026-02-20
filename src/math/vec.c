/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:51:09 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/17 00:21:31 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vec3	vec_add(t_vec3 first, t_vec3 sec)
{
	t_vec3	res;

	res.e[X] = first.e[X] + sec.e[X];
	res.e[Y] = first.e[Y] + sec.e[Y];
	res.e[Z] = first.e[Z] + sec.e[Z];
	return (res);
}

t_vec3	vec_sub(t_vec3 first, t_vec3 sec)
{
	t_vec3	res;

	res.e[X] = first.e[X] - sec.e[X];
	res.e[Y] = first.e[Y] - sec.e[Y];
	res.e[Z] = first.e[Z] - sec.e[Z];
	return (res);
}

double	vec_dot(t_vec3 first, t_vec3 sec)
{
	return ((first.e[X] * sec.e[X]) + (first.e[Y] * sec.e[Y]) + (first.e[Z]
			* sec.e[Z]));
}

void	vec_scale(t_vec3 *vec, double scalar)
{
	vec->e[X] *= scalar;
	vec->e[Y] *= scalar;
	vec->e[Z] *= scalar;
}
