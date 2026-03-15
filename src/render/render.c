#include "../../inc/miniRT.h"

static int	clamp_color(int color_val)
{
	if (color_val < 0)
		return (0);
	if (color_val > 255)
		return (255);
	return (color_val);
}

static void	draw_pixel(t_data *data, int x, int y, t_hit *hit)
{
	int		color;
	t_vec3	base_col;
	double	intensity;

	if (hit->obj)
	{
		base_col = hit->obj->color;
		intensity = intensity_on_hp(data->scene, *hit);
		base_col = vec_scale(base_col, intensity);
		
		color = (clamp_color((int)base_col.e[0]) << 16)
			| (clamp_color((int)base_col.e[1]) << 8)
			| clamp_color((int)base_col.e[2]);
		my_mlx_pixel_put(&data->img, x, y, color);
	}
	else
		my_mlx_pixel_put(&data->img, x, y, BLACK);
}

static void	render_pixel(t_data *data, int x, int y, int cam_in)
{
	t_ray	ray;
	t_hit	hit;

	if (cam_in)
		my_mlx_pixel_put(&data->img, x, y, BLACK);
	else
	{
		ray.pnt = data->scene.camera.origin;
		ray.dir = map_pixel((double)x, (double)y, data->scene.camera);
		hit = closest_hit(data->scene.objects, ray);
		draw_pixel(data, x, y, &hit);
	}
}

void	render_scene(t_data *data)
{
	int	x;
	int	y;
	int	cam_in;

	cam_in = is_cam_inside(&data->scene);
	y = 0;
	while (y < (int)HEIGHT)
	{
		x = 0;
		while (x < (int)WIDTH)
		{
			render_pixel(data, x, y, cam_in);
			x++;
		}
		y++;
	}
}