/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:58:05 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/20 16:17:13 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	main(void)
{
	t_data	data;

	data.mlx = NULL;
	data.win = NULL;
	data.img.ptr = NULL;
	
	empty_scene(&data); 

	init_mlx(&data);
	setup_hooks(&data);
	
	my_mlx_pixel_put(&data.img, 960, 540, 0x00FF0000); 
	
	mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}

// int	main(void)
// {
// 	t_data	data;

// 	data.mlx = NULL;
// 	data.win = NULL;
// 	data.img.ptr = NULL;
// 	init_mlx(&data);
// 	setup_hooks(&data);
// 	my_mlx_pixel_put(&data.img, 960, 540, 0x00FF0000);
// 	mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 0, 0);
// 	mlx_loop(data.mlx);
// 	return (0);
// }
