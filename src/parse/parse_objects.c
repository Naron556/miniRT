
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

	if (count_tokens(tokens) < 4 || count_tokens(tokens) > 5)
		error_exit_parse(scene, tokens, "Invalid Sphere format");
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		error_exit_parse(scene, tokens, "Memory allocation failed");
	obj->type = SPHERE;
	obj->shape.sp.center = parse_vec3(tokens[1], scene, tokens);
	obj->center = obj->shape.sp.center;
	
	obj->shape.sp.radius = ft_atof(tokens[2]) / 2.0; 
	obj->shape.sp.ref = 50.0;
	
	obj->color = parse_color(tokens[3], scene, tokens);
	if (tokens[4])
	{
		obj->has_texture = 1;
		obj->tex_path = ft_strdup(tokens[4]);
	}
	add_object(scene, obj);
}

static void	init_plane_texture(t_object *obj, int count, char **tokens)
{
	obj->has_texture = 0;
	obj->tex_path = NULL;
	obj->shape.pl.scale = 10.0;
	if (count >= 5)
	{
		obj->has_texture = 1;
		obj->tex_path = ft_strdup(tokens[4]);
	}
	if (count == 6)
	{
		obj->shape.pl.scale = ft_atof(tokens[5]);
		if (obj->shape.pl.scale <= 0.0)
			obj->shape.pl.scale = 10.0;
	}
}


void	parse_plane(t_scene *scene, char **tokens)
{
	t_object	*obj;
	t_vec3		up;

	if (count_tokens(tokens) < 4 || count_tokens(tokens) > 6)
		error_exit_parse(scene, tokens, "Invalid Plane format");
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		error_exit_parse(scene, tokens, "Memory allocation failed");
	obj->type = PLANE;
	obj->shape.pl.point = parse_vec3(tokens[1], scene, tokens);
	obj->center = obj->shape.pl.point;
	obj->shape.pl.dir = vec_normalize(parse_vec3(tokens[2], scene, tokens));
	up = (t_vec3){{0, 1, 0}};
	if (fabs(obj->shape.pl.dir.e[1]) == 1.0)
		up = (t_vec3){{1, 0, 0}};
	obj->shape.pl.u_axis = vec_normalize(vec_cross(up, obj->shape.pl.dir));
	obj->shape.pl.v_axis = vec_cross(obj->shape.pl.dir, obj->shape.pl.u_axis);
	
	obj->shape.pl.ref = 50.0;
	
	obj->color = parse_color(tokens[3], scene, tokens);
	init_plane_texture(obj, count_tokens(tokens), tokens);
	add_object(scene, obj);
}

void	parse_cylinder(t_scene *scene, char **tokens)
{
	t_object	*obj;

	if (count_tokens(tokens) < 6 || count_tokens(tokens) > 7)
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
	
	obj->shape.cy.ref = 50.0;
	
	obj->color = parse_color(tokens[5], scene, tokens);
	if (tokens[6])
	{
		obj->has_texture = 1;
		obj->tex_path = ft_strdup(tokens[6]);
	}
	add_object(scene, obj);
}