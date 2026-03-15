/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:32:22 by yamohamm          #+#    #+#             */
/*   Updated: 2026/03/15 20:36:06 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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
	scene->camera.dir = vec_normalize(parse_vec3(tokens[2], scene, tokens));
	fov_degrees = ft_atof(tokens[3]);
	if (fov_degrees < 0 || fov_degrees > 180)
		error_exit_parse(scene, tokens, "FOV out of range (0-180)");
	scene->camera.fov = cnv_to_rad(fov_degrees);
	cam_count++;
}

void	parse_light(t_scene *scene, char **tokens)
{
	if (scene->light_count > 0)
		error_exit_parse(scene, tokens, "Duplicate light (L)");
	if (count_tokens(tokens) != 4)
		error_exit_parse(scene, tokens, "Invalid Light format");
	scene->lights = malloc(sizeof(t_light));
	if (!scene->lights)
		error_exit_parse(scene, tokens, "Memory allocation failed");
	scene->lights->origin = parse_vec3(tokens[1], scene, tokens);
	scene->lights->ratio = ft_atof(tokens[2]);
	scene->lights->color = parse_color(tokens[3], scene, tokens);
	if (scene->lights->ratio < 0.0 || scene->lights->ratio > 1.0)
		error_exit_parse(scene, tokens, "Light ratio out of range");
	scene->light_count++;
}
