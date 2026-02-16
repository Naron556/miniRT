/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:58:05 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/16 22:51:45 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	exit_error(char *msg, t_data *data)
{
	printf("Error\n%s\n", msg);
	if (data)
		exit(1);
	exit(1);
}

int	main(void)
{
	t_data	data;

	data.mlx = NULL;
	data.win = NULL;
	data.img.ptr = NULL;
	init_mlx(&data);
	setup_hooks(&data);
	my_mlx_pixel_put(&data.img, 960, 540, 0x00FF0000);
	mlx_put_image_to_window(data.mlx, data.win, data.img.ptr, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
