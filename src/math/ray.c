/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:08:06 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/25 20:33:38 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

double	cnv_to_rad(double angle)
{
	return ((angle * PI) / 180.0);
}

t_vec3	map_pixel(double i, double j, t_camera cam)
{
	t_vec3	ray_dir;
	double	vp_width;
	double	vp_height;
	double	u;
	double	v;

	vp_width = 2.0 * tan(cam.fov / 2.0);
	vp_height = vp_width / ASPECT;
	u = (i + 0.5) / WIDTH - 0.5;
	v = 0.5 - (j + 0.5) / HEIGHT;
	ray_dir.e[x] = cam.dir.e[x] + (u * vp_width * cam.right.e[x]) + (v
			* vp_height * cam.up.e[x]);
	ray_dir.e[y] = cam.dir.e[y] + (u * vp_width * cam.right.e[y]) + (v
			* vp_height * cam.up.e[y]);
	ray_dir.e[z] = cam.dir.e[z] + (u * vp_width * cam.right.e[z]) + (v
			* vp_height * cam.up.e[z]);
	return (vec_normalize(ray_dir));
}

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

t_quad_eq	cy_quad(t_ray ray, t_object cy)
{
	t_quad_eq	eq;
	t_vec3		cp;

	cp = vec_sub(ray.pnt, cy.center);
	eq.t1 = -1.0;
	eq.t2 = -1.0;
	eq.a = vec_dot(ray.dir, ray.dir) - pow(vec_dot(ray.dir, cy.shape.cy.axis),
			2.0);
	eq.b = 2.0 * (vec_dot(ray.dir, cp) - vec_dot(ray.dir, cy.shape.cy.axis)
			* vec_dot(cp, cy.shape.cy.axis));
	eq.c = vec_dot(cp, cp) - pow(vec_dot(cp, cy.shape.cy.axis), 2.0)
		- pow(cy.shape.cy.radius, 2.0);
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

int	t_in_height(t_ray ray, t_object cy, double t)
{
	t_vec3	hp;
	double	dist;

	if (t <= 0.0001)
		return (0);
	hp = vec_add(ray.pnt, vec_scale(ray.dir, t));
	dist = vec_dot(cy.shape.cy.axis, vec_sub(hp, cy.center));
	if (dist >= -(cy.shape.cy.height / 2.0) && dist <= (cy.shape.cy.height
			/ 2.0))
		return (1);
	return (0);
}

t_quad_eq	cy_intsec(t_ray ray, t_object cy)
{
	t_quad_eq	eq;

	eq = cy_quad(ray, cy);
	if (eq.delta < 0.0)
		return (eq);
	if (!t_in_height(ray, cy, eq.t1))
		eq.t1 = -1.0;
	if (!t_in_height(ray, cy, eq.t2))
		eq.t2 = -1.0;
	return (eq);
}

t_hit	closest_hit(t_object *objs, t_ray ray, t_camera cam)
{
	t_hit	closest;
	t_hit	temp;

	closest.t = INFINITY;
	closest.obj = NULL;
	while (objs)
	{
		temp.t = obj_dist(*objs, ray, cam);
		if (temp.t > 0.0001 && temp.t < closest.t)
		{
			closest.t = temp.t;
			closest.obj = objs;
		}
		objs = objs->next;
	}
	if (closest.obj)
	{
		closest.hit_point = vec_add(ray.pnt, vec_scale(ray.dir, closest.t));
		closest.normal = get_normal(ray, closest);
	}
	return (closest);
}

double	obj_dist(t_object obj, t_ray ray, t_camera cam)
{
	t_quad_eq	eq;

	if (obj.type == PLANE)
		return (pl_intsec(ray, obj));
	else if (obj.type == SPHERE || obj.type == CYLINDER)
	{
		if (obj.type == SPHERE)
			eq = sp_intsec(ray, obj);
		else
			eq = cy_intsec(ray, obj);
		if (eq.t1 == eq.t2)
			return (eq.t1);
		if (eq.t1 < eq.t2 && eq.t1 > 0.0001)
			return (eq.t1);
		else if (eq.t2 > 0.0001)
			return (eq.t2);
	}
	return (-1.0);
}

t_vec3	get_normal(t_ray ray, t_hit hit)
{
	t_vec3	res;
	double	dist;
	t_vec3	axis_point;

	if (hit.obj->type == SPHERE)
		res = vec_normalize(vec_sub(hit.hit_point, hit.obj->center));
	else if (hit.obj->type == PLANE)
	{
		res = hit.obj->shape.pl.dir;
		if (vec_dot(ray.dir, res) > 0)
			res = vec_scale(res, -1.0);
	}
	else if (hit.obj->type == CYLINDER)
	{
		dist = vec_dot(hit.obj->shape.cy.axis, vec_sub(hit.hit_point,
					hit.obj->center));
		axis_point = vec_add(hit.obj->center, vec_scale(hit.obj->shape.cy.axis,
					dist));
		res = vec_normalize(vec_sub(hit.hit_point, axis_point));
	}
	return (res);
}
