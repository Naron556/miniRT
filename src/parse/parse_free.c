
#include "../../inc/miniRT.h"

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

// void	error_exit(char *error_msg, t_data *data)
// {
// 	printf("Error\n%s\n", error_msg);
// 	if (data)
// 		free_scene(&data->scene); // Free whatever was loaded before the crash
// 	exit(1);
// }
