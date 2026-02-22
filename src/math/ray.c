/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:08:06 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/22 18:44:39 by arkadiusz        ###   ########.fr       */
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

void	sp_intsec(t_quad_eq *eq, t_ray ray, t_camera cam, t_object sphere)
{
	t_vec3	co;

	eq->t1 = -1.0;
	eq->t2 = -1.0;
	co = vec_sub(cam.origin, sphere.shape.sp.center);
	eq->a = vec_dot(ray.dir, ray.dir);
	eq->b = 2 * vec_dot(co, ray.dir);
	eq->c = vec_dot(co, co) - pow(sphere.shape.sp.radius, 2);
	eq->delta = pow(eq->b, 2) - (4.0 * (eq->a * eq->c));
	if (eq->delta < 0)
		return ;
	else if (eq->delta == 0)
	{
		eq->t1 = -eq->b / (2 * eq->a);
		eq->t1 = eq->t1;
	}
	else
	{
		eq->t1 = (-eq->b - sqrt(eq->delta)) / (2 * eq->a);
		eq->t2 = (-eq->b + sqrt(eq->delta)) / (2 * eq->a);
	}
}

double	pl_intsec(t_ray ray, t_object sp)
{
	double	t;

	if (fabs(vec_dot(ray.dir, sp.shape.pl.dir)) < 1e-6)
		return (-1.0);
	t = vec_dot(vec_sub(ray.pnt, sp.shape.pl.point), sp.shape.pl.dir);
	if (t > 0.0001)
		return (t);
	return (-1.0);
}
