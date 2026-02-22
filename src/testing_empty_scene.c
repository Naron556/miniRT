#include "../inc/miniRT.h"

/* Helper function to quickly create a t_vec3 */
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
	t_object	*sphere;

	// 1. Scene counts
	data->scene.amb_count = 1;
	data->scene.light_count = 1; 
	// cam_count removed since it's not in t_scene in miniRT.h

	// 2. Ambient Light
	data->scene.ambient.ratio = 0.2;
	data->scene.ambient.color = make_vec(255.0, 255.0, 255.0);

	// 3. Camera (Placed at origin, looking down the +Z axis)
	data->scene.camera.origin = make_vec(0.0, 0.0, 0.0);
	data->scene.camera.dir = make_vec(0.0, 0.0, 1.0);
	data->scene.camera.dir = vec_normalize(data->scene.camera.dir); // Always normalize direction!
	data->scene.camera.fov = 70.0;

	// 4. Light
	data->scene.lights = malloc(sizeof(t_light));
	if (!data->scene.lights)
		return ; // Protect malloc in real code
	data->scene.lights->origin = make_vec(0.0, 10.0, 0.0);
	data->scene.lights->ratio = 0.8;
	data->scene.lights->color = make_vec(255.0, 255.0, 255.0);
	data->scene.lights->next = NULL;

	// 5. Objects - Add a Sphere to test intersections!
	sphere = malloc(sizeof(t_object));
	if (!sphere)
		return ;
	sphere->type = SPHERE;
	sphere->color = make_vec(255.0, 0.0, 0.0); // Red
	sphere->shape.sp.center = make_vec(0.0, 0.0, 5.0); // 5 units in front of the camera
	sphere->shape.sp.radius = 2.0;
	sphere->next = NULL;

	data->scene.objects = sphere;
}
