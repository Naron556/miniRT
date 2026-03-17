/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:32:28 by yamohamm          #+#    #+#             */
/*   Updated: 2026/03/15 20:39:36 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	add_object(t_scene *scene, t_object *new_obj)
{
	t_object	*tmp;

	if (!scene->objects)
		scene->objects = new_obj;
	else
	{
		tmp = scene->objects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_obj;
	}
}

void	parse_sphere(t_scene *scene, char **tokens)
{
	t_object	*obj;

	if (count_tokens(tokens) != 4)
		error_exit_parse(scene, tokens, "Invalid Sphere format");
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		error_exit_parse(scene, tokens, "Memory allocation failed");
	obj->type = SPHERE;
	obj->shape.sp.center = parse_vec3(tokens[1], scene, tokens);
	obj->center = obj->shape.sp.center;
	obj->shape.sp.radius = ft_atof(tokens[2]) / 2.0;
	obj->color = parse_color(tokens[3], scene, tokens);
	add_object(scene, obj);
}

void	parse_plane(t_scene *scene, char **tokens)
{
	t_object	*obj;

	if (count_tokens(tokens) != 4)
		error_exit_parse(scene, tokens, "Invalid Plane format");
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		error_exit_parse(scene, tokens, "Memory allocation failed");
	obj->type = PLANE;
	obj->shape.pl.point = parse_vec3(tokens[1], scene, tokens);
	obj->center = obj->shape.pl.point;
	obj->shape.pl.dir = vec_normalize(parse_vec3(tokens[2], scene, tokens));
	obj->color = parse_color(tokens[3], scene, tokens);
	add_object(scene, obj);
}

void	parse_cylinder(t_scene *scene, char **tokens)
{
	t_object	*obj;

	if (count_tokens(tokens) != 6)
		error_exit_parse(scene, tokens, "Invalid Cylinder format");
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		error_exit_parse(scene, tokens, "Memory allocation failed");
	obj->type = CYLINDER;
	obj->shape.cy.center = parse_vec3(tokens[1], scene, tokens);
	obj->center = obj->shape.cy.center;
	obj->shape.cy.axis = vec_normalize(parse_vec3(tokens[2], scene, tokens));
	obj->shape.cy.radius = ft_atof(tokens[3]) / 2.0;
	obj->shape.cy.height = ft_atof(tokens[4]);
	obj->color = parse_color(tokens[5], scene, tokens);
	add_object(scene, obj);
}
