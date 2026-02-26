#include "../../inc/miniRT.h"

void	parse_ambient(t_scene *scene, char **tokens)
{
	if (scene->amb_count > 0)
	{
		printf("%s", ERR_DUP);
		exit(1);
	}
	if (count_tokens(tokens) != 3)
	{
		printf("Error\nInvalid Ambient Light format\n");
		exit(1);
	}
	scene->ambient.ratio = ft_atof(tokens[1]);
	scene->ambient.color = parse_color(tokens[2]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
	{
		printf("Error\nAmbient ratio out of range (0.0-1.0)\n");
		exit(1);
	}
	scene->amb_count++;
}

void	parse_camera(t_scene *scene, char **tokens)
{
	static int	cam_count = 0;
	double		fov_degrees;

	if (cam_count > 0)
	{
		printf("%s", ERR_DUP);
		exit(1);
	}
	if (count_tokens(tokens) != 4)
	{
		printf("Error\nInvalid Camera format\n");
		exit(1);
	}
	scene->camera.origin = parse_vec3(tokens[1]);
	scene->camera.dir = vec_normalize(parse_vec3(tokens[2]));
	fov_degrees = ft_atof(tokens[3]);
	if (fov_degrees < 0 || fov_degrees > 180)
	{
		printf("Error\nFOV out of range (0-180)\n");
		exit(1);
	}
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
	{
		printf("Error\nInvalid Light format\n");
		exit(1);
	}
	new_light = malloc(sizeof(t_light));
	if (!new_light)
	{
		printf("%s", ERR_MEM);
		exit(1);
	}
	new_light->origin = parse_vec3(tokens[1]);
	new_light->ratio = ft_atof(tokens[2]);
	new_light->color = parse_color(tokens[3]);
	new_light->next = NULL;
	if (new_light->ratio < 0.0 || new_light->ratio > 1.0)
	{
		printf("Error\nLight ratio out of range (0.0-1.0)\n");
		exit(1);
	}
	add_light(scene, new_light);
}

