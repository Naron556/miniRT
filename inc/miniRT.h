/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:56:10 by aoperacz          #+#    #+#             */
/*   Updated: 2026/02/08 03:14:06 by yamohamm         ###   ########.fr       */
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
	t_color					color;
}							t_ambient;

typedef struct s_light
{
	double					x;
	double					y;
	double					z;
	double					brightness;
	t_color					color;
}							t_light;

typedef struct s_sphere
{
	double					x;
	double					y;
	double					z;
	double					diam;
	t_color					color;
	struct 					s_sphere *next;
}							t_sphere;

typedef struct s_plane
{
	double					x;
	double					y;
	double					z;
	double					vec_x;
	double					vec_y;
	double					vec_z;
	t_color					color;
	struct 					s_plane *next;
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
	t_color					color;
	struct 					s_cylinder *next;
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

typedef struct s_color
{
	int						r;
	int						g;
	int 					b;
}							t_color;

typedef struct s_img 
{
	void					*ptr;
	char					*addr;
	int						bpp;
	int						len;
	int						endian;
}							t_img;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	t_img				img;
	t_scene				scene;
}						t_data;

#endif