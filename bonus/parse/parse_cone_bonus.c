/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:25:10 by yamohamm          #+#    #+#             */
/*   Updated: 2026/03/16 19:26:06 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

void	parse_cone(t_scene *scene, char **tokens)
{
	t_object	*obj;

	if (count_tokens(tokens) < 6 || count_tokens(tokens) > 7)
		error_exit_parse(scene, tokens, "Invalid Cone format");
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		error_exit_parse(scene, tokens, "Memory allocation failed");
	obj->type = CONE;
	obj->shape.co.center = parse_vec3(tokens[1], scene, tokens);
	obj->center = obj->shape.co.center;
	obj->shape.co.axis = vec_normalize(parse_vec3(tokens[2], scene, tokens));
	
	obj->shape.co.radius = ft_atof(tokens[3]) / 2.0; 
	obj->shape.co.height = ft_atof(tokens[4]);
	
	obj->shape.co.ref = 50.0; // Default specular reflection
	
	obj->color = parse_color(tokens[5], scene, tokens);
	
	if (tokens[6])
	{
		obj->has_texture = 1;
		obj->tex_path = ft_strdup(tokens[6]);
	}
	add_object(scene, obj);
}
