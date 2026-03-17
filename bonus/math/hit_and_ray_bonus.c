/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_and_ray_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:08:06 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/17 21:57:55 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

t_vec3	map_pixel(double i, double j, t_camera cam)
{
	t_vec3	ray_dir;
	double	vp_width;
	double	vp_height;
	double	u;
	double	v;

	vp_width = 2.0 * tan(cam.fov / 2.0);
	vp_height = vp_width / (WIDTH / HEIGHT);
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

static void	finalize_hit(t_ray ray, t_hit *closest)
{
	if (!closest->obj)
		return ;
	closest->hit_point = vec_add(ray.pnt, vec_scale(ray.dir, closest->t));
	closest->normal = get_normal(ray, *closest);
	if (closest->obj->type == SPHERE)
		closest->ref = closest->obj->shape.sp.ref;
	else if (closest->obj->type == PLANE)
		closest->ref = closest->obj->shape.pl.ref;
	else if (closest->obj->type == CYLINDER)
		closest->ref = closest->obj->shape.cy.ref;
}

t_hit	closest_hit(t_object *objs, t_ray ray)
{
	t_hit	closest;
	t_hit	temp;

	closest.t = INFINITY;
	closest.obj = NULL;
	while (objs)
	{
		temp.t = obj_dist(objs, ray, &temp);
		if (temp.t > 0.0001 && temp.t < closest.t)
		{
			closest.t = temp.t;
			closest.normal_type = temp.normal_type;
			closest.obj = objs;
		}
		objs = objs->next;
	}
	finalize_hit(ray, &closest);
	return (closest);
}

double	obj_dist(t_object *obj, t_ray ray, t_hit *hit)
{
	t_quad_eq	eq;
	double		t;

	t = -1.0;
	if (obj->type == PLANE)
		return (pl_intsec(ray, *obj));
	else if (obj->type == SPHERE || obj->type == CYLINDER || obj->type == CONE)
	{
		if (obj->type == SPHERE)
			eq = sp_intsec(ray, *obj);
		else if (obj->type == CYLINDER)
			eq = cy_intsec(ray, *obj, hit);
		else
			eq = co_intsec(ray, *obj, hit);
		if (eq.t1 > 0.0001)
			t = eq.t1;
		if (eq.t2 > 0.0001 && (t < 0 || eq.t2 < t))
			t = eq.t2;
	}
	return (t);
}
