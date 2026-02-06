/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:56:10 by aoperacz          #+#    #+#             */
/*   Updated: 2026/02/06 19:21:45 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "libft/libft.h"
# include "libmlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_camera		t_camera;
typedef struct s_ambient	t_ambient;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_scene		t_scene;

typedef struct s_camera
{
	double					x;
	double					y;
	double					z;
	double					vec_x;
	double					vec_y;
	double					vec_z;
	int						FOV;
}							t_camera;

typedef struct s_ambient
{
	double					ratio;
	int						RED;
	int						GREEN;
	int						BLUE;
}							t_ambient;

typedef struct s_light
{
	double					x;
	double					y;
	double					z;
	double					brightness;
	int						RED;
	int						GREEN;
	int						BLUE;
}							t_light;

typedef struct s_sphere
{
	double					x;
	double					y;
	double					z;
	double					diam;
	int						RED;
	int						GREEN;
	int						BLUE;
}							t_sphere;

typedef struct s_plane
{
	double					x;
	double					y;
	double					z;
	double					vec_x;
	double					vec_y;
	double					vec_z;
	int						RED;
	int						GREEN;
	int						BLUE;
}							t_plane;

typedef struct s_cylinder
{
	double					x;
	double					z;
	double					y;
	double					vec_x;
	double					vec_y;
	double					vec_z;
	double					diam;
	double					hght;
	int						RED;
	int						GREEN;
	int						BLUE;
}							t_cylinder;

typedef struct s_scene //maybe delete pointers, not exactly sure yet
{
	t_camera				*camera;
	t_ambient				*ambient;
	t_light					*light;
	t_sphere				*sphere;
	t_plane					*plane;
	t_cylinder				*cynlinder;
}							t_scene;

#endif