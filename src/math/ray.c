/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:08:06 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/20 17:10:39 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

double	cnv_to_rad(double angle)
{
	return ((angle * PI) / 180.0);
}

void	cam_vec(t_camera *cam)
{
	cam->right = vec_cross((t_vec3){0, 1, 0}, cam->dir);
	cam->right = vec_normalize(cam->right);
	cam->up = vec_cross(cam->dir, cam->right);
	cam->up = vec_normalize(cam->up);
}

t_vec3	map_pixel(double x, double y, t_camera cam)
{
	t_vec3	ray_dir;
	double	vp_width;
	double	vp_height;
	double	u;
	double	v;

	vp_width = 2.0 * tan(cam.FOV / 2.0);
	vp_height = vp_width / ASPECT;
	u = (x + 0.5) / WIDTH - 0.5;
	v = 0.5 - (y + 0.5) / HEIGHT;
	ray_dir.e[X] = cam.dir.e[X] + (u * vp_width * cam.right.e[X]) + (v
			* vp_height * cam.up.e[X]);
	ray_dir.e[Y] = cam.dir.e[Y] + (u * vp_width * cam.right.e[Y]) + (v
			* vp_height * cam.up.e[Y]);
	ray_dir.e[Z] = cam.dir.e[Z] + (u * vp_width * cam.right.e[Z]) + (v
			* vp_height * cam.up.e[Z]);
	return (vec_normalize(ray_dir));
}
