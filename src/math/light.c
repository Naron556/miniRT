/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:33:53 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/06 20:14:40 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

double	intensity_on_hp(t_scene scene, t_hit hit)
{
	double	res;
	double	dot;
	t_vec3	hit_to_light;
	t_light	*lights;

	res = scene.ambient.ratio;
	if (scene.light_count == 0)
		return (res);
	lights = scene.lights;
	while (lights)
	{
		hit_to_light = vec_normalize(vec_sub(lights->origin, hit.hit_point));
		if (hp_in_shadow(hit, scene.objects, *lights))
		{
			lights = lights->next;
			continue ;
		}
		dot = vec_dot(hit_to_light, hit.normal);
		if (dot > 0.0)
			res += lights->ratio * dot;
		lights = lights->next;
	}
	if (res > 1.0)
		return (1.0);
	return (res);
}

int	hp_in_shadow(t_hit hit, t_object *objs, t_light light)
{
	t_ray		shadow_ray;
	t_object	*temp;
	t_vec3		shadow_dir;
	double		light_dist;
	double		ob_dist;

	shadow_dir = vec_sub(light.origin, hit.hit_point);
	light_dist = vec_len(shadow_dir) - 0.00001;
	shadow_ray.pnt = vec_add(hit.hit_point, vec_scale(hit.normal, 0.00001));
	shadow_ray.dir = vec_normalize(shadow_dir);
	temp = objs;
	while (temp)
	{
		ob_dist = obj_dist(temp, shadow_ray);
		if (ob_dist > 0.0 && ob_dist < light_dist)
			return (1);
		temp = temp->next;
	}
	return (0);
}
