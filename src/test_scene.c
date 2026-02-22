#include "inc/miniRT.h"

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
	data->scene.amb_count = 1;
	data->scene.light_count = 1; 

	// 2. Ambient Light
	data->scene.ambient.ratio = 0.2;
	data->scene.ambient.color = make_vec(255.0, 255.0, 255.0);

	// 3. Camera
	data->scene.camera.origin = make_vec(0.0, 0.0, 0.0);
	data->scene.camera.dir = make_vec(0.0, 0.0, 0.8);
	data->scene.camera.dir = vec_normalize(data->scene.camera.dir); // Always normalize direction!
	data->scene.camera.fov = 70.0;
	//they need to calculate the camera's `right` and `up` vectors in their code)

	// 4. Light
	data->scene.lights = malloc(sizeof(t_light));
	data->scene.lights->origin = make_vec(0.0, 10.0, 0.0);
	data->scene.lights->ratio = 0.8;
	data->scene.lights->color = make_vec(255.0, 255.0, 255.0);
	data->scene.lights->next = NULL;

	// 5. Explicitly set objects to NULL so their loop safely skips intersections
	data->scene.objects = NULL;
}