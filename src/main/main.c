/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:09:03 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/13 18:10:01 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img.ptr = NULL;
	data->img.addr = NULL;
	data->scene.amb_count = 0;
	data->scene.light_count = 0;
	data->scene.lights = NULL;
	data->scene.objects = NULL;
	data->tex_cache = NULL;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("%s", ERR_ARGS);
		return (1);
	}
	
	init_data(&data);
	parse_file(&data, argv[1]);
	cam_vec(&data.scene.camera);
	init_mlx(&data);
	
	load_object_textures(&data);
	
	render_scene(&data);
	setup_hooks(&data);
	
	mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 0, 0);
	mlx_loop(data.mlx);
	
	return (0);
}
