#include "../../inc/miniRT_bonus.h"

static t_xpm	*get_cached_texture(t_data *data, char *path)
{
	t_tex_cache	*curr;

	curr = data->tex_cache;
	while (curr)
	{
		if (ft_strncmp(curr->path, path, ft_strlen(path) + 1) == 0)
			return (&curr->xpm);
		curr = curr->next;
	}
	return (NULL);
}

static t_xpm	*add_to_cache(t_data *data, char *path)
{
	t_tex_cache	*new_node;
	t_xpm		*xpm;

	new_node = malloc(sizeof(t_tex_cache));
	if (!new_node)
		return (NULL);
	new_node->path = ft_strdup(path);
	xpm = &new_node->xpm;
	xpm->ptr = mlx_xpm_file_to_image(data->mlx, path,
			&xpm->width, &xpm->height);
	if (!xpm->ptr)
	{
		free(new_node->path);
		free(new_node);
		return (NULL);
	}
	xpm->addr = mlx_get_data_addr(xpm->ptr, &xpm->bpp,
			&xpm->len, &xpm->endian);
	new_node->next = data->tex_cache;
	data->tex_cache = new_node;
	return (xpm);
}

static void	assign_texture(t_data *data, t_object *obj)
{
	t_xpm	*c_xpm;

	c_xpm = get_cached_texture(data, obj->tex_path);
	if (!c_xpm)
	{
		c_xpm = add_to_cache(data, obj->tex_path);
		if (!c_xpm)
		{
			printf("Error\nCould not load texture: %s\n", obj->tex_path);
			free_scene(&data->scene);
			exit(1);
		}
	}
	obj->texture = *c_xpm;
}

void	load_object_textures(t_data *data)
{
	t_object	*obj;

	obj = data->scene.objects;
	while (obj)
	{
		if (obj->has_texture && obj->tex_path
			&& ft_strncmp(obj->tex_path, "checker", 8) != 0)
		{
			assign_texture(data, obj);
		}
		obj = obj->next;
	}
}
