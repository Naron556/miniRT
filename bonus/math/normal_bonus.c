/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:34:48 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/17 19:11:11 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

t_vec3	get_normal(t_ray ray, t_hit hit)
{
	t_vec3	res;

	res = (t_vec3){{0.0, 0.0, 0.0}};
	if (hit.obj->type == SPHERE)
		res = vec_normalize(vec_sub(hit.hit_point, hit.obj->center));
	else if (hit.obj->type == PLANE)
	{
		res = hit.obj->shape.pl.dir;
		if (vec_dot(ray.dir, res) > 0)
			res = vec_scale(res, -1.0);
	}
	else if (hit.obj->type == CYLINDER)
		res = cy_normal(hit);
	else if (hit.obj->type == CONE)
		res = co_normal(hit);
	return (res);
}

void	cy_normal_type(t_hit *hit, t_quad_eq *eq, double t1, double t2)
{
	if (t1 > 0.0001 && (eq->t1 < 0 || t1 < eq->t1))
		eq->t1 = t1;
	if (t2 > 0.0001 && (eq->t2 < 0 || t2 < eq->t2))
		eq->t2 = t2;
	if (eq->t1 < 0 && eq->t2 < 0)
		return ;
	if (eq->t1 == t1 && (eq->t2 < 0 || eq->t1 < eq->t2))
		hit->normal_type = top_cap;
	else if (eq->t2 == t2 && (eq->t1 < 0 || eq->t2 < eq->t1))
		hit->normal_type = bot_cap;
	else
		hit->normal_type = standard;
}

t_vec3	cy_normal(t_hit hit)
{
	t_vec3	res;
	double	dist;
	t_vec3	axis_point;

	if (hit.normal_type == standard)
	{
		dist = vec_dot(hit.obj->shape.cy.axis, vec_sub(hit.hit_point,
					hit.obj->center));
		axis_point = vec_add(hit.obj->center, vec_scale(hit.obj->shape.cy.axis,
					dist));
		res = vec_normalize(vec_sub(hit.hit_point, axis_point));
	}
	else if (hit.normal_type == bot_cap)
		res = vec_scale(hit.obj->shape.cy.axis, -1.0);
	else
		res = hit.obj->shape.cy.axis;
	return (res);
}

void	co_normal_type(t_hit *hit, t_quad_eq *eq, double t_cap)
{
	double	t;

	t = -1.0;
	if (eq->t1 > 0.0001)
		t = eq->t1;
	if (eq->t2 > 0.0001 && (t < 0 || eq->t2 < t))
		t = eq->t2;
	if (t_cap > 0.0001 && (t < 0 || t_cap < t))
	{
		eq->t1 = t_cap;
		hit->normal_type = bot_cap;
	}
	else if (t > 0.0001)
	{
		eq->t1 = t;
		hit->normal_type = standard;
	}
	else
		eq->t1 = -1.0;
}

t_vec3	co_normal(t_hit hit)
{
	t_vec3	res;
	t_vec3	vp;
	double	dist;
	double	m_val;

	if (hit.normal_type == standard)
	{
		vp = vec_sub(hit.hit_point, hit.obj->shape.co.vrt);
		dist = vec_dot(vp, hit.obj->shape.co.axis);
		m_val = 1.0 + hit.obj->shape.co.k_sq;
		res = vec_sub(vp, vec_scale(hit.obj->shape.co.axis, m_val * dist));
		res = vec_normalize(res);
	}
	else
		res = vec_scale(hit.obj->shape.co.axis, -1.0);
	return (res);
}
