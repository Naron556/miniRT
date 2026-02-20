/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_progress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:08:06 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/02/20 14:29:05 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

double	cnv_to_rad(int angle)
{
	return ((double)angle * 180.0 / PI);
}

void	cam_vec(t_camera *cam)
{
	cam->right = vec_cross(cam->dir, (t_vec3){0, 1, 0});
	cam->right = vec_normalize(cam->right);
	cam->up = vec_cross(cam->right, cam->dir);
	cam->up = vec_normalize(cam->up);
}
