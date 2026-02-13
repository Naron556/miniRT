/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:56:10 by aoperacz          #+#    #+#             */
/*   Updated: 2026/02/13 23:16:42 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "gnl/get_next_line.h"
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

typedef enum e_coords
{
						X = 0,
						Y = 1,
						Z = 2
}						t_coords;

//use color.e[R]
typedef enum e_rgb
{
						R = 0,
						G = 1,
						B = 2
}						t_rgb;

// an array for Coordinate (x,y,z), Orientation (vx,vy,vz), and Color (r,g,b)
// vec.e[X]  or  vec.e[R]
// vec.e[Y]  or  vec.e[G]
// vec.e[Z]  or  vec.e[B]
typedef struct s_vec3
{
						double	e[3];
}						t_vec3;


typedef struct s_img
{
	void				*ptr;
	char				*addr;
	int					bpp;
	int					len;
	int					endian;
}						t_img;

typedef struct s_ambient
{
	double				ratio;
	t_vec3				color;
}						t_ambient;

typedef struct s_camera
{
	t_vec3				origin;// position (x,y,z)
	t_vec3				dir; // orientation vector
	int					FOV;
}						t_camera;

typedef struct s_light
{
	t_vec3				origin;
	double				ratio;
	t_vec3				color;
	struct s_light		*next;
}						t_light;

typedef struct s_sphere
{
	t_vec3				center;
	double				radius; // (diameter / 2)
	t_vec3				color;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	t_vec3				point;
	t_vec3				normal;
	t_vec3				color;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				coords;
	double				radius;
	double				height;
	t_vec3				color;
	struct s_cylinder	*next;
}	t_cylinder;


typedef struct s_scene
{
	t_ambient			ambient;
	t_camera			camera;
	t_light				*lights;
	t_sphere			*spheres;
	t_plane				*planes;
	t_cylinder			*cylinders;
	int					amb_count;
	int					cam_count;
	int					light_count;
}	t_scene;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	t_img				img;
	t_scene				scene;
}						t_data;

// void	init_mlx(t_data *data);
// void	setup_hooks(t_data *data);

#endif