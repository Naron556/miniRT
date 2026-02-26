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
	{
		printf("Error\nInvalid Sphere format\n");
		exit(1);
	}
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit(1);
	obj->type = SPHERE;
	obj->shape.sp.center = parse_vec3(tokens[1]);
	obj->center = obj->shape.sp.center;
	obj->shape.sp.radius = ft_atof(tokens[2]);
	obj->color = parse_color(tokens[3]);
	obj->next = NULL;
	add_object(scene, obj);
}

void	parse_plane(t_scene *scene, char **tokens)
{
	t_object	*obj;

	if (count_tokens(tokens) != 4)
	{
		printf("Error\nInvalid Plane format\n");
		exit(1);
	}
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit(1);
	obj->type = PLANE;
	obj->shape.pl.point = parse_vec3(tokens[1]);
	obj->center = obj->shape.pl.point;
	obj->shape.pl.dir = vec_normalize(parse_vec3(tokens[2]));
	obj->color = parse_color(tokens[3]);
	obj->next = NULL;
	add_object(scene, obj);
}

void	parse_cylinder(t_scene *scene, char **tokens)
{
	t_object	*obj;

	if (count_tokens(tokens) != 6)
	{
		printf("Error\nInvalid Cylinder format\n");
		exit(1);
	}
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit(1);
	obj->type = CYLINDER;
	obj->shape.cy.center = parse_vec3(tokens[1]);
	obj->center = obj->shape.cy.center;
	obj->shape.cy.axis = vec_normalize(parse_vec3(tokens[2]));
	obj->shape.cy.radius = ft_atof(tokens[3]);
	obj->shape.cy.height = ft_atof(tokens[4]);
	obj->color = parse_color(tokens[5]);
	obj->next = NULL;
	add_object(scene, obj);
}
