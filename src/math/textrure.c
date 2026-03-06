#include "../../inc/miniRT.h"

static t_vec3	get_checker_color(t_object *obj, double u, double v, double s)
{
	int		u2;
	int		v2;
	t_vec3	white;

	u2 = (int)floor(u * s);
	v2 = (int)floor(v * s);
	white = (t_vec3){{255.0, 255.0, 255.0}};
	if ((u2 + v2) % 2 == 0)
		return (obj->color);
	return (white);
}

static t_vec3	get_image_color(t_xpm *tex, double u, double v)
{
	int		x;
	int		y;
	char	*dst;
	int		color;
	t_vec3	rgb;

	u = u - floor(u);
	v = v - floor(v);
	x = (int)(u * tex->width);
	y = (int)(v * tex->height);
	if (x >= tex->width)
		x = tex->width - 1;
	if (y >= tex->height)
		y = tex->height - 1;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	dst = tex->addr + (y * tex->len + x * (tex->bpp / 8));
	color = *(unsigned int *)dst;
	rgb.e[0] = (color >> 16) & 0xFF;
	rgb.e[1] = (color >> 8) & 0xFF;
	rgb.e[2] = color & 0xFF;
	return (rgb);
}

static t_vec3	get_cylinder_uv(t_object *obj, t_hit *hit)
{
	t_vec3	local_p;
	t_vec3	aux;
	t_vec3	axes[2];
	double	uv[2];

	local_p = vec_sub(hit->hit_point, obj->center);
	aux = (t_vec3){{0, 1, 0}};
	if (fabs(obj->shape.cy.axis.e[1]) == 1.0)
		aux = (t_vec3){{1, 0, 0}};
	axes[0] = vec_normalize(vec_cross(obj->shape.cy.axis, aux));
	axes[1] = vec_cross(obj->shape.cy.axis, axes[0]);
	uv[0] = 0.5 + (atan2(vec_dot(local_p, axes[1]),
				vec_dot(local_p, axes[0])) / (2.0 * PI));
	uv[1] = vec_dot(local_p, obj->shape.cy.axis) / obj->shape.cy.height;
	if (ft_strncmp(obj->tex_path, "checker", 8) == 0)
		return (get_checker_color(obj, uv[0], uv[1], 15.0));
	if (!obj->texture.addr)
		return (obj->color);
	return (get_image_color(&obj->texture, uv[0], uv[1]));
}

static t_vec3	get_sphere_uv(t_object *obj, t_hit *hit)
{
	t_vec3	n;
	double	u;
	double	v;
	double	y_val;

	n = vec_normalize(vec_sub(hit->hit_point, obj->center));
	u = 0.5 + (atan2(n.e[2], n.e[0]) / (2.0 * PI));
	y_val = n.e[1];
	if (y_val > 1.0)
		y_val = 1.0;
	if (y_val < -1.0)
		y_val = -1.0;
	v = 0.5 - (asin(y_val) / PI);
	if (ft_strncmp(obj->tex_path, "checker", 8) == 0)
		return (get_checker_color(obj, u, v, 20.0));
	if (!obj->texture.addr)
		return (obj->color);
	return (get_image_color(&obj->texture, u, v));
}

t_vec3	apply_texture(t_hit *hit)
{
	double	u;
	double	v;

	if (!hit->obj->has_texture || !hit->obj->tex_path)
		return (hit->obj->color);
	if (hit->obj->type == SPHERE)
		return (get_sphere_uv(hit->obj, hit));
	if (hit->obj->type == CYLINDER)
		return (get_cylinder_uv(hit->obj, hit));
	if (hit->obj->type == PLANE)
	{
		u = vec_dot(hit->hit_point, hit->obj->shape.pl.u_axis)
			/ hit->obj->shape.pl.scale;
		v = vec_dot(hit->hit_point, hit->obj->shape.pl.v_axis)
			/ hit->obj->shape.pl.scale;
		if (ft_strncmp(hit->obj->tex_path, "checker", 8) == 0)
			return (get_checker_color(hit->obj, u, v, 10.0));
		if (!hit->obj->texture.addr)
			return (hit->obj->color);
		return (get_image_color(&hit->obj->texture, u, v));
	}
	return (hit->obj->color);
}
