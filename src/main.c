#include "../../inc/miniRT.h"

static void	draw_pixel(t_data *data, int x, int y, t_hit *hit)
{
	int	color;

	if (hit->obj)
	{
		color = ((int)hit->obj->color.e[0] << 16)
			| ((int)hit->obj->color.e[1] << 8)
			| ((int)hit->obj->color.e[2]);
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
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(data, x, y, cam_in);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("%s", ERR_ARGS);
		return (1);
	}
	data.mlx = NULL;
	data.win = NULL;
	data.img.ptr = NULL;
	parse_file(&data, argv[1]);
	cam_vec(&data.scene.camera);
	init_mlx(&data);
	setup_hooks(&data);
	render_scene(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
