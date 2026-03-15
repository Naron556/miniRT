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
