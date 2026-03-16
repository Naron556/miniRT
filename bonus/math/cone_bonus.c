/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:28:06 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/16 19:17:16 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

t_quad_eq	co_quad(t_cone *cn, t_ray ray)
{
	t_quad_eq	eq;
	t_vec3		pv;

	eq.t1 = -1.0;
	eq.t2 = -1.0;
	cn->k_sq = pow(cn->radius / cn->height, 2.0);
	cn->vrt = vec_add(cn->center, vec_scale(cn->axis, cn->height / 2));
	pv = vec_sub(ray.pnt, cn->vrt);
	eq.a = pow(vec_dot(ray.dir, cn->axis), 2.0) * (1 + cn->k_sq)
		- vec_dot(ray.dir, ray.dir);
	eq.b = 2 * (vec_dot(ray.dir, cn->axis) * vec_dot(pv, cn->axis) * (1
				+ cn->k_sq) - vec_dot(ray.dir, pv));
	eq.c = pow(vec_dot(pv, cn->axis), 2.0) * (1 + cn->k_sq) - vec_dot(pv, pv);
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

t_quad_eq	co_intsec(t_ray ray, t_object cn, t_hit *hit)
{
	t_quad_eq	eq;
	t_vec3		cap;
	double		ct;

	eq = co_quad(&cn.shape.co, ray);
	if (!co_t_in_height(ray, eq.t1, cn))
		eq.t1 = -1.0;
	if (!co_t_in_height(ray, eq.t2, cn))
		eq.t2 = -1.0;
	cap = vec_sub(cn.shape.co.center, vec_scale(cn.shape.co.axis,
				cn.shape.co.height / 2.0));
	ct = cap_intsec(ray, cn.shape.co.axis, cap, cn.shape.co.radius);
	co_normal_type(hit, &eq, ct);
	return (eq);
}

int	co_t_in_height(t_ray ray, double t, t_object cn)
{
	t_vec3	hp;
	t_vec3	vp;
	double	dist;

	if (t < 0.0001)
		return (0);
	hp = vec_add(ray.pnt, vec_scale(ray.dir, t));
	vp = vec_sub(hp, cn.shape.co.vrt);
	dist = vec_dot(vp, cn.shape.co.axis);
	if (dist >= 0 && dist <= cn.shape.co.height)
		return (1);
	return (0);
}
