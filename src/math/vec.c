/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:51:09 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/20 16:29:22 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vec3	vec_add(t_vec3 first, t_vec3 sec)
{
	t_vec3	res;

	res.e[x] = first.e[x] + sec.e[x];
	res.e[y] = first.e[y] + sec.e[y];
	res.e[z] = first.e[z] + sec.e[z];
	return (res);
}

t_vec3	vec_sub(t_vec3 first, t_vec3 sec)
{
	t_vec3	res;

	res.e[x] = first.e[x] - sec.e[x];
	res.e[y] = first.e[y] - sec.e[y];
	res.e[z] = first.e[z] - sec.e[z];
	return (res);
}

double	vec_dot(t_vec3 first, t_vec3 sec)
{
	return ((first.e[x] * sec.e[x]) + (first.e[y] * sec.e[y]) + (first.e[z]
			* sec.e[z]));
}

void	vec_scale(t_vec3 *vec, double scalar)
{
	vec->e[x] *= scalar;
	vec->e[y] *= scalar;
	vec->e[z] *= scalar;
}
