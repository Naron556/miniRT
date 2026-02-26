#include "../../inc/miniRT.h"

static t_vec3	make_vec(double x, double y, double z)
{
	t_vec3 vec;
	
	vec.e[0] = x;
	vec.e[1] = y;
	vec.e[2] = z;
	return (vec);
}



void	empty_scene(t_data *data)
{
	data->scene.amb_count = 1;
	data->scene.light_count = 1; 

	// 1. Ambient Light
	data->scene.ambient.ratio = 0.2;
	data->scene.ambient.color = make_vec(255.0, 255.0, 255.0);

	// 2. Camera
	data->scene.camera.origin = make_vec(0.0, 0.0, 0.0);
	data->scene.camera.dir = make_vec(0.0, 0.0, 1.0);
	data->scene.camera.dir = vec_normalize(data->scene.camera.dir);
	data->scene.camera.fov = cnv_to_rad(70.0);

	// 3. Light
	data->scene.lights = malloc(sizeof(t_light));
	data->scene.lights->origin = make_vec(0.0, 10.0, 0.0);
	data->scene.lights->ratio = 0.8;
	data->scene.lights->color = make_vec(255.0, 255.0, 255.0);
	data->scene.lights->next = NULL;

	data->scene.objects = NULL;
}

void test_sphere_scene(t_data *data)
{
	empty_scene(data);
	
	// Create a single red object
	t_object *object = malloc(sizeof(t_object));
	if (!object)
		return;
		
	object->type = SPHERE;
	object->color = make_vec(255.0, 0.0, 0.0);
	
	// Use the union 'shape.sp' to set object properties
	object->shape.sp.center = make_vec(0.0, 0.0, 15.0); // Placed 5 units in front of camera
	object->shape.sp.radius = 2.0;
	
	object->next = NULL;

	data->scene.objects = object;
}
