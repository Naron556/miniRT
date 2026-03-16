/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_in_obj_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:00:22 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/16 22:00:30 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

static int	is_inside_cy(t_vec3 cam, t_object *obj)
{
	t_vec3	v;
	double	proj;
	double	d2;

	v = vec_sub(cam, obj->shape.cy.center);
	proj = vec_dot(v, obj->shape.cy.axis);
	d2 = vec_dot(v, v) - (proj * proj);
	if (d2 < (obj->shape.cy.radius * obj->shape.cy.radius) && proj >
		-(obj->shape.cy.height / 2.0) && proj < (obj->shape.cy.height / 2.0))
		return (1);
	return (0);
}

int	is_cam_inside(t_scene *scene)
{
	t_object	*obj;
	double		r_sq;
	t_vec3		cam_to_center;

	obj = scene->objects;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			r_sq = obj->shape.sp.radius * obj->shape.sp.radius;
			cam_to_center = vec_sub(scene->camera.origin, obj->shape.sp.center);
			if (vec_dot(cam_to_center, cam_to_center) < r_sq)
				return (1);
		}
		else if (obj->type == CYLINDER)
		{
			if (is_inside_cy(scene->camera.origin, obj))
				return (1);
		}
		obj = obj->next;
	}
	return (0);
}
