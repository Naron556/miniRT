/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:59:32 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/17 21:38:40 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_data *data)
{
	free_texture_cache(data);
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_scene(&data->scene);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	printf("Key Pressed: %d\n", keycode);
	if (keycode == ESC_KEY_LINUX || keycode == ESC_KEY_MAC)
		close_window(data);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
	{
		free(data->mlx);
		exit(1);
	}
	data->img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.ptr)
	{
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
		exit(1);
	}
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.len, &data->img.endian);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, key_hook, data);
}
