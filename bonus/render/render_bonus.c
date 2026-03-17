/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:50:49 by yamohamm          #+#    #+#             */
/*   Updated: 2026/03/17 17:50:51 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

int	clamp_color(int color_val)
{
	if (color_val < 0)
		return (0);
	if (color_val > 255)
		return (255);
	return (color_val);
}

static t_vec3	get_color(t_data *data, double px, double py)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	color;
	double	intensity;

	ray.pnt = data->scene.camera.origin;
	ray.dir = map_pixel(px, py, data->scene.camera);
	hit = closest_hit(data->scene.objects, ray);
	if (hit.obj)
	{
		color = apply_texture(&hit);
		intensity = intensity_on_hp(data->scene, hit);
		return (vec_scale(color, intensity));
	}
	return ((t_vec3){{0, 0, 0}});
}

static void	render_pixel(t_data *data, int x, int y, int cam_in)
{
	t_vec3	final_color;
	double	px;
	double	py;
	int		i;

	if (cam_in)
	{
		my_mlx_pixel_put(&data->img, x, y, BLACK);
		return ;
	}
	final_color = (t_vec3){{0, 0, 0}};
	i = 0;
	while (i < 9)
	{
		px = (double)x + ((double)rand() / RAND_MAX) - 0.5;
		py = (double)y + ((double)rand() / RAND_MAX) - 0.5;
		final_color = vec_add(final_color, get_color(data, px, py));
		i++;
	}
	final_color = vec_scale(final_color, 1.0 / 9.0);
	my_mlx_pixel_put(&data->img, x, y, get_color_int(final_color));
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
		while (x < (int)WIDTH)
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
	int				chunk_size;

	chunk_size = (int)HEIGHT / THREADS;
	i = 0;
	while (i < THREADS)
	{
		th_data[i].data = data;
		th_data[i].start_y = i * chunk_size;
		th_data[i].end_y = (i + 1) * chunk_size;
		if (i == THREADS - 1)
			th_data[i].end_y = (int)HEIGHT;
		th_data[i].cam_in = is_cam_inside(&data->scene);
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
