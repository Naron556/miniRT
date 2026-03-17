/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_things_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 21:21:21 by yamohamm          #+#    #+#             */
/*   Updated: 2026/03/17 21:21:22 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

t_vec3	parse_dir_vec(char *str, t_scene *scene, char **tokens)
{
	t_vec3	dir;

	dir = parse_vec3(str, scene, tokens);
	if (dir.e[0] < -1.0 || dir.e[0] > 1.0 || dir.e[1] < -1.0
		|| dir.e[1] > 1.0 || dir.e[2] < -1.0 || dir.e[2] > 1.0)
		error_exit_parse(scene, tokens, "Dir vector out of range [-1, 1]");
	if (dir.e[0] == 0.0 && dir.e[1] == 0.0 && dir.e[2] == 0.0)
		error_exit_parse(scene, tokens, "Dir vector cannot be 0,0,0");
	return (vec_normalize(dir));
}

void	parse_ambient(t_scene *scene, char **tokens)
{
	if (scene->amb_count > 0)
		error_exit_parse(scene, tokens, "Duplicate ambient light");
	if (count_tokens(tokens) != 3)
		error_exit_parse(scene, tokens, "Invalid Ambient Light format");
	scene->ambient.ratio = ft_atof(tokens[1]);
	scene->ambient.color = parse_color(tokens[2], scene, tokens);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		error_exit_parse(scene, tokens, "Ambient ratio out of range (0.0-1.0)");
	scene->amb_count++;
}

void	parse_camera(t_scene *scene, char **tokens)
{
	static int	cam_count = 0;
	double		fov_degrees;

	if (cam_count > 0)
		error_exit_parse(scene, tokens, "Duplicate camera");
	if (count_tokens(tokens) != 4)
		error_exit_parse(scene, tokens, "Invalid Camera format");
	scene->camera.origin = parse_vec3(tokens[1], scene, tokens);
	scene->camera.dir = parse_dir_vec(tokens[2], scene, tokens);
	fov_degrees = ft_atof(tokens[3]);
	if (fov_degrees < 0 || fov_degrees > 180)
		error_exit_parse(scene, tokens, "FOV out of range (0-180)");
	scene->camera.fov = cnv_to_rad(fov_degrees);
	cam_count++;
}

static void	add_light(t_scene *scene, t_light *new_light)
{
	t_light	*tmp;

	if (!scene->lights)
		scene->lights = new_light;
	else
	{
		tmp = scene->lights;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
	}
	scene->light_count++;
}

void	parse_light(t_scene *scene, char **tokens)
{
	t_light	*new_light;

	if (count_tokens(tokens) != 4)
		error_exit_parse(scene, tokens, "Invalid Light format");
	new_light = malloc(sizeof(t_light));
	if (!new_light)
		error_exit_parse(scene, tokens, "Memory allocation failed");
	new_light->origin = parse_vec3(tokens[1], scene, tokens);
	new_light->ratio = ft_atof(tokens[2]);
	new_light->color = parse_color(tokens[3], scene, tokens);
	new_light->next = NULL;
	if (new_light->ratio < 0.0 || new_light->ratio > 1.0)
		error_exit_parse(scene, tokens, "Light ratio out of range");
	add_light(scene, new_light);
}