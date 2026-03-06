/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_and_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:08:06 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/06 21:32:39 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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

t_hit	closest_hit(t_object *objs, t_ray ray)
{
	t_hit	closest;
	t_hit	temp;

	closest.t = INFINITY;
	closest.obj = NULL;
	while (objs)
	{
		temp.t = obj_dist(objs, ray);
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

double	obj_dist(t_object *obj, t_ray ray)
{
	t_quad_eq	eq;
	double		t;

	if (obj->type == PLANE)
		return (pl_intsec(ray, *obj));
	else if (obj->type == SPHERE || obj->type == CYLINDER)
	{
		t = -1.0;
		if (obj->type == SPHERE)
			eq = sp_intsec(ray, *obj);
		else
			eq = cy_intsec(ray, *obj);
		if (eq.t1 > 0.0001)
			t = eq.t1;
		if (eq.t2 > 0.0001 && (t < 0 || eq.t2 < t))
			t = eq.t2;
	}
	return (t);
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
