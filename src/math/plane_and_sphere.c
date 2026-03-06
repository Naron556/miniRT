/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:43:21 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/05 15:45:54 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_quad_eq	sp_intsec(t_ray ray, t_object sphere)
{
	t_quad_eq	eq;
	t_vec3		co;

	eq.t1 = -1.0;
	eq.t2 = -1.0;
	co = vec_sub(ray.pnt, sphere.shape.sp.center);
	eq.a = vec_dot(ray.dir, ray.dir);
	eq.b = 2 * vec_dot(co, ray.dir);
	eq.c = vec_dot(co, co) - pow(sphere.shape.sp.radius, 2);
	eq.delta = pow(eq.b, 2) - (4.0 * (eq.a * eq.c));
	if (eq.delta == 0.0)
	{
		eq.t1 = -eq.b / (2 * eq.a);
		eq.t2 = eq.t1;
	}
	else if (eq.delta > 0.0)
	{
		eq.t1 = (-eq.b - sqrt(eq.delta)) / (2 * eq.a);
		eq.t2 = (-eq.b + sqrt(eq.delta)) / (2 * eq.a);
	}
	return (eq);
}

double	pl_intsec(t_ray ray, t_object pl)
{
	double	t;
	double denom;

	denom = vec_dot(ray.dir, pl.shape.pl.dir);
	if (fabs(denom) < 1e-6)
		return (-1.0);
	t = vec_dot(vec_sub(pl.shape.pl.point, ray.pnt), pl.shape.pl.dir) / denom;
	if (t > 0.0001)
		return (t);
	return (-1.0);
}
