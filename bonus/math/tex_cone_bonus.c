
#include "../../inc/miniRT_bonus.h"

t_vec3	get_cone_uv(t_object *obj, t_hit *hit)
{
	t_vec3	local_p;
	t_vec3	aux;
	t_vec3	axes[2];
	double	uv[2];

	local_p = vec_sub(hit->hit_point, obj->center);
	aux = (t_vec3){{0, 1, 0}};
	if (fabs(obj->shape.co.axis.e[1]) == 1.0)
		aux = (t_vec3){{1, 0, 0}};
	axes[0] = vec_normalize(vec_cross(obj->shape.co.axis, aux));
	axes[1] = vec_cross(obj->shape.co.axis, axes[0]);
	uv[0] = 0.5 + (atan2(vec_dot(local_p, axes[1]),
				vec_dot(local_p, axes[0])) / (2.0 * PI));
	uv[1] = vec_dot(local_p, obj->shape.co.axis) / obj->shape.co.height;
	if (ft_strncmp(obj->tex_path, "checker", 8) == 0)
		return (get_checker_color(obj, uv[0], uv[1], 15.0));
	if (!obj->texture.addr)
		return (obj->color);
	return (get_image_color(&obj->texture, uv[0], uv[1]));
}