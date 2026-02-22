/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:58:05 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/22 22:44:59 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void render_scene(t_data *data)
{
	int x;
	int y;
	t_ray ray;
	t_quad_eq eq;
	int color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// Shoot ray from camera
			ray.pnt = data->scene.camera.origin;
			ray.dir = map_pixel((double)x, (double)y, data->scene.camera);

			// Check intersection with our hardcoded sphere
			if (data->scene.objects && data->scene.objects->type == SPHERE)
			{
				eq = sp_intsec(ray, data->scene.camera, *data->scene.objects);
				
				if (eq.delta >= 0 && eq.t1 > 0)
					color = RED; // Hit!
				else
					color = BLACK; // Miss!
			}
			else
				color = BLACK;

			my_mlx_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_data	data;

	data.mlx = NULL;
	data.win = NULL;
	data.img.ptr = NULL;
	
	// 1. Load the mock scene
	test_sphere_scene(&data); 

	// 2. Calculate camera 'up' and 'right' vectors so map_pixel works!
	cam_vec(&data.scene.camera);

	// 3. Initialize window and image
	init_mlx(&data);
	setup_hooks(&data);
	
	// 4. Raytrace the scene
	render_scene(&data);
	
	// 5. Display to screen
	mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
