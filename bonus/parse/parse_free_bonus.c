/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:06:35 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/16 23:04:58 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

void	free_texture_cache(t_data *data)
{
	t_tex_cache	*curr;
	t_tex_cache	*next;

	curr = data->tex_cache;
	while (curr)
	{
		next = curr->next;
		if (curr->xpm.ptr)
			mlx_destroy_image(data->mlx, curr->xpm.ptr);
		if (curr->path)
			free(curr->path);
		free(curr);
		curr = next;
	}
	data->tex_cache = NULL;
}

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*tmp_obj;
	t_light		*light;
	t_light		*tmp_light;

	obj = scene->objects;
	while (obj)
	{
		tmp_obj = obj->next;
		if (obj->tex_path)
			free(obj->tex_path);
		free(obj);
		obj = tmp_obj;
	}
	light = scene->lights;
	while (light)
	{
		tmp_light = light->next;
		free(light);
		light = tmp_light;
	}
}

void	error_exit_parse(t_scene *scene, char **tokens, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (tokens)
		free_tokens(tokens);
	if (scene)
		free_scene(scene);
	exit(1);
}
int	get_color_int(t_vec3 col)
{
	int	r;
	int	g;
	int	b;

	r = clamp_color((int)col.e[0]);
	g = clamp_color((int)col.e[1]);
	b = clamp_color((int)col.e[2]);
	return ((r << 16) | (g << 8) | b);
}
