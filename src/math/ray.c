/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:08:06 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/22 23:32:31 by arkadiusz        ###   ########.fr       */
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

t_quad_eq	sp_intsec(t_ray ray, t_camera cam, t_object sphere)
{
	t_quad_eq	eq;
	t_vec3		co;

	eq.t1 = -1.0;
	eq.t2 = -1.0;
	co = vec_sub(cam.origin, sphere.shape.sp.center);
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

	if (fabs(vec_dot(ray.dir, pl.shape.pl.dir)) < 1e-6)
		return (-1.0);
	t = vec_dot(vec_sub(ray.pnt, pl.shape.pl.point), pl.shape.pl.dir);
	if (t > 0.0001)
		return (t);
	return (-1.0);
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
			closest.hit_point = vec_scale(ray.dir, closest.t);
			closest.normal = vec_cross(vec_sub(closest.hit_point, closest.obj->shape));
		}
		objs = objs->next;
	}
	return (closest);
}

double	obj_dist(t_object obj, t_ray ray, t_camera cam)
{
	t_quad_eq	eq;

	if (obj.type == PLANE)
		return (pl_intsec(ray, obj));
	else if (obj.type == SPHERE)
	{
		eq = sp_intsec(ray, cam, obj);
		if (eq.t1 == eq.t2)
			return (eq.t1);
		if (eq.t1 < eq.t2)
			return (eq.t1);
		else
			return (eq.t2);
	}
	else if (obj.type == CYLINDER)
	{
		return (-1.0); // quadratic function for cylinder
	}
	return (-1.0);
}

t_vec3	get_normal(t_ray ray, t_hit hit)
{
	t_vec3 res;

	if (hit.obj->type == SPHERE)
	{
		res = vec_normalize(vec_sub(hit.hit_point, hit.obj->center));
	}
}
