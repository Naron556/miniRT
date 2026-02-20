/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:56:10 by aoperacz          #+#    #+#             */
/*   Updated: 2026/02/20 14:23:51 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>
# define ESC_KEY_LINUX 65307
# define ESC_KEY_MAC 53
# define WHITE 0x00FFFFFF
# define BLACK 0x0000000
# define PI 3.141592653589793

typedef enum e_coords
{
	X = 0,
	Y = 1,
	Z = 2
}						t_coords;

// use color.e[R]
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
	double				e[3];
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
	t_vec3				origin;
	t_vec3				dir;
	t_vec3				right;
	t_vec3				up;
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
	double radius; // (diameter / 2)
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
}						t_cylinder;

typedef struct s_ray
{
	t_vec3				pnt;
	t_vec3				dir;
}						t_ray;

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
}						t_scene;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	t_img				img;
	t_scene				scene;
}						t_data;

/*---------- /src/math ----------*/

void					vec_scale(t_vec3 *vec, double scalar);
double					vec_dot(t_vec3 first, t_vec3 sec);
t_vec3					vec_sub(t_vec3 first, t_vec3 sec);
t_vec3					vec_add(t_vec3 first, t_vec3 sec);
double					vec_len(t_vec3 vec);
t_vec3					vec_cross(t_vec3 first, t_vec3 second);
t_vec3					vec_normalize(t_vec3 vec);

void					init_mlx(t_data *data);
void					setup_hooks(t_data *data);
int						close_window(t_data *data);
void					my_mlx_pixel_put(t_img *img, int x, int y, int color);
int						main(void);
int						key_hook(int keycode, t_data *data);

#endif