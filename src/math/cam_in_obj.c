#include "../../inc/miniRT.h"

static double	get_dist_sq(t_vec3 a, t_vec3 b)
{
	double	dx;
	double	dy;
	double	dz;

	dx = a.e[0] - b.e[0];
	dy = a.e[1] - b.e[1];
	dz = a.e[2] - b.e[2];
	return (dx * dx + dy * dy + dz * dz);
}

static int	is_inside_cy(t_vec3 cam, t_object *obj)
{
	t_vec3	v;
	double	proj;
	double	d2;

	v.e[0] = cam.e[0] - obj->shape.cy.center.e[0];
	v.e[1] = cam.e[1] - obj->shape.cy.center.e[1];
	v.e[2] = cam.e[2] - obj->shape.cy.center.e[2];
	proj = v.e[0] * obj->shape.cy.axis.e[0]
		+ v.e[1] * obj->shape.cy.axis.e[1]
		+ v.e[2] * obj->shape.cy.axis.e[2];
	d2 = (v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]) - (proj * proj);
	if (d2 < (obj->shape.cy.radius * obj->shape.cy.radius)
		&& proj > -(obj->shape.cy.height / 2.0)
		&& proj < (obj->shape.cy.height / 2.0))
		return (1);
	return (0);
}

int	is_cam_inside(t_scene *scene)
{
	t_object	*obj;
	double		r_sq;

	obj = scene->objects;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			r_sq = obj->shape.sp.radius * obj->shape.sp.radius;
			if (get_dist_sq(scene->camera.origin, obj->shape.sp.center) < r_sq)
				return (1);
		}
		else if (obj->type == CYLINDER)
		{
			if (is_inside_cy(scene->camera.origin, obj))
				return (1);
		}
		obj = obj->next;
	}
	return (0);
}
