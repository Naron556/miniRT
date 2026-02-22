/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:44:01 by yamohamm          #+#    #+#             */
/*   Updated: 2026/02/22 23:11:42 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "libmlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define ESC_KEY_MAC 53
# define ESC_KEY_LINUX 65307
# define WHITE 0x00FFFFFF
# define BLACK 0x0000000
# define RED 0xFF0000
# define PI 3.141592653589793
# define WIDTH (double)1920
# define HEIGHT (double)1080
# define ASPECT (WIDTH / HEIGHT)
# define ERR_ARGS "Error\nWrong number of arguments\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_MEM "Error\nMemory allocation failed\n"
# define ERR_VAL "Error\nInvalid value in scene file\n"
# define ERR_DUP "Error\nDuplicate scene element (A, C, or L)\n"

typedef enum e_coords
{
	x = 0,
	y,
	z
}					t_coords;

typedef enum e_rgb
{
	r = 0,
	g,
	b
}					t_rgb;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}					t_type;

typedef struct s_vec3
{
	double			e[3];
}					t_vec3;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				len;
	int				endian;
}					t_img;

typedef struct s_ambient
{
	double			ratio;
	t_vec3			color;
}					t_ambient;

typedef struct s_camera
{
	t_vec3			origin;
	t_vec3			dir;
	t_vec3			right;
	t_vec3			up;
	double			fov;
}					t_camera;

typedef struct s_light
{
	t_vec3			origin;
	double			ratio;
	t_vec3			color;
	struct s_light	*next;
}					t_light;

typedef struct s_sphere
{
	t_vec3			center;
	double			radius;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			dir;
}					t_plane;

typedef struct s_cylinder

{
	t_vec3			center;
	t_vec3			axis;
	double			radius;
	double			height;
}					t_cylinder;

typedef union u_shape
{
	t_sphere		sp;
	t_plane			pl;
	t_cylinder		cy;
}					t_shape;

typedef struct s_object
{
	t_type			type;
	t_vec3			center;
	t_vec3			color;
	t_shape			shape;
	struct s_object	*next;
}					t_object;

typedef struct s_ray
{
	t_vec3			pnt;
	t_vec3			dir;
}					t_ray;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			*lights;
	t_object		*objects;
	int				amb_count;
	int				light_count;
}					t_scene;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_scene			scene;
}					t_data;

typedef struct s_quad_eq
{
	double			delta;
	double			t1;
	double			t2;
	double			a;
	double			b;
	double			c;
}					t_quad_eq;

typedef struct s_hit
{
	double			t;
	t_vec3			hit_point;
	t_vec3			normal;
	t_object		*obj;

}					t_hit;

void				init_mlx(t_data *data);
void				empty_scene(t_data *data);

/*---------- teststuff ----------*/
void				test_sphere_scene(t_data *data);
void				empty_scene(t_data *data);

/*---------- /src/math ----------*/

t_vec3				vec_scale(t_vec3 vec, double scalar);
double				vec_dot(t_vec3 first, t_vec3 sec);
t_vec3				vec_sub(t_vec3 first, t_vec3 sec);
t_vec3				vec_add(t_vec3 first, t_vec3 sec);
double				vec_len(t_vec3 vec);
t_vec3				vec_cross(t_vec3 first, t_vec3 second);
t_vec3				vec_normalize(t_vec3 vec);
void				cam_vec(t_camera *cam);
t_vec3				map_pixel(double i, double j, t_camera cam);
double				cnv_to_rad(double angle);
t_quad_eq			sp_intsec(t_ray ray, t_camera cam, t_object sphere);
double				pl_intsec(t_ray ray, t_object sp);

void				init_mlx(t_data *data);
void				setup_hooks(t_data *data);
int					close_window(t_data *data);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
int					main(void);
int					key_hook(int keycode, t_data *data);

#endif