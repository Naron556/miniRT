/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:33:53 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/13 12:52:11 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

double	intensity_on_hp(t_scene scene, t_hit hit)
{
	double	res;
	double	dot;
	t_vec3	hit_to_light;
	t_light	*lights;

	if (scene.light_count == 0)
		return (scene.ambient.ratio);
	res = scene.ambient.ratio;
	lights = scene.lights;
	while (lights)
	{
		if (!hp_in_shadow(hit, scene.objects, *lights))
		{
			hit_to_light = vec_normalize(vec_sub(lights->origin, hit.hit_point));
			dot = vec_dot(hit_to_light, hit.normal);
			if (dot > 0.0)
				res += lights->ratio * dot;
			res += specular(hit, hit_to_light, scene.camera.origin, lights->ratio);
		}
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
		ob_dist = obj_dist(temp, shadow_ray, &hit);
		if (ob_dist > 0.0 && ob_dist < light_dist)
			return (1);
		temp = temp->next;
	}
	return (0);
}

double	specular(t_hit hit, t_vec3 hit_to_light, t_vec3 cam_point, double ratio)
{
	double	res;
	double	dot;
	t_vec3	cp;
	t_vec3	r;

	dot = vec_dot(hit_to_light, hit.normal);
	if (dot <= 0)
		return (0);
	cp = vec_normalize(vec_sub(cam_point, hit.hit_point));
	r = vec_sub(vec_scale(hit.normal, 2.0 * dot), hit_to_light);
	r = vec_normalize(r);
	res = vec_dot(cp, r);
	if (res > 0)
		res = pow(res, hit.ref) * ratio;
	else
		return (0);
	return (res);
}
