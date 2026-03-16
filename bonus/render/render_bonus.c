/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 22:08:25 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/16 22:08:56 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

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
	int		r;
	int		g;
	int		b;

	if (hit->obj)
	{
		base_col = apply_texture(hit);
		intensity = intensity_on_hp(data->scene, *hit);
		base_col = vec_scale(base_col, intensity);
		r = clamp_color((int)base_col.e[0]);
		g = clamp_color((int)base_col.e[1]);
		b = clamp_color((int)base_col.e[2]);
		color = (r << 16) | (g << 8) | b;
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
	int				cam_in;
	int				chunk_size;

	cam_in = is_cam_inside(&data->scene);
	chunk_size = (int)HEIGHT / THREADS;
	i = 0;
	while (i < THREADS)
	{
		th_data[i].data = data;
		th_data[i].start_y = i * chunk_size;
		th_data[i].end_y = (i + 1) * chunk_size;
		if (i == THREADS - 1)
			th_data[i].end_y = (int)HEIGHT;
		th_data[i].cam_in = cam_in;
		pthread_create(&threads[i], NULL, render_chunk, &th_data[i]);
		i++;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
}
