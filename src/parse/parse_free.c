
#include "../../inc/miniRT.h"

void	free_scene(t_scene *scene)
{
	t_object	*tmp_obj;
	t_light		*tmp_light;

	while (scene->objects)
	{
		tmp_obj = scene->objects->next;
		free(scene->objects);
		scene->objects = tmp_obj;
	}

	while (scene->lights)
	{
		tmp_light = scene->lights->next;
		free(scene->lights);
		scene->lights = tmp_light;
	}
}
