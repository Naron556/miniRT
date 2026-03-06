#include "../../inc/miniRT.h"

typedef struct s_thread_data
{
	t_data	*data;
	int		start_y;
	int		end_y;
	int		cam_in;
}	t_thread_data;

static void	draw_pixel(t_data *data, int x, int y, t_hit *hit)
{
	int		color;
	t_vec3	final_color;

	if (hit->obj)
	{
		final_color = apply_texture(hit); 
		color = ((int)final_color.e[0] << 16)
			| ((int)final_color.e[1] << 8)
			| ((int)final_color.e[2]);
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

static void	*render_chunk(void *arg)
{
	t_thread_data	*th;
	int				x;
	int				y;

	th = (t_thread_data *)arg;
	y = th->start_y;
	while (y < th->end_y)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(th->data, x, y, th->cam_in);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	render_scene(t_data *data)
{
	pthread_t		threads[THREADS];
	t_thread_data	th_data[THREADS];
	int				i;
	int				cam_in;
	int				chunk_size;

	cam_in = is_cam_inside(&data->scene);
	chunk_size = HEIGHT / THREADS;
	i = 0;
	while (i < THREADS)
	{
		th_data[i].data = data;
		th_data[i].start_y = i * chunk_size;
		th_data[i].end_y = (i + 1) * chunk_size;
		if (i == THREADS - 1)
			th_data[i].end_y = HEIGHT;
		th_data[i].cam_in = cam_in;
		pthread_create(&threads[i], NULL, render_chunk, &th_data[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
