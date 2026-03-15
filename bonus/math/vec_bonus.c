/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:51:09 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/15 17:14:12 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

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

t_vec3	vec_scale(t_vec3 vec, double scalar)
{
	t_vec3	res;

	res.e[x] = vec.e[x] * scalar;
	res.e[y] = vec.e[y] * scalar;
	res.e[z] = vec.e[z] * scalar;
	return (res);
}

void	cam_vec(t_camera *cam)
{
	cam->right = vec_cross((t_vec3){{0, 1, 0}}, cam->dir);
	cam->right = vec_normalize(cam->right);
	cam->up = vec_cross(cam->dir, cam->right);
	cam->up = vec_normalize(cam->up);
}
