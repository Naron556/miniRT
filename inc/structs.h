#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_coords
{
	x = 0,
	y,
	z
}						t_coords;

typedef enum e_rgb
{
	r = 0,
	g,
	b
}						t_rgb;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}						t_type;

typedef enum e_normal
{
	standard,
	bot_cap,
	top_cap
}						t_normal;

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

typedef struct s_xpm
{
	void				*ptr;
	char				*addr;
	int					bpp;
	int					len;
	int					endian;
	int					width;
	int					height;
}						t_xpm;

typedef struct s_tex_cache
{
	char				*path;
	t_xpm				xpm;
	struct s_tex_cache	*next;
}						t_tex_cache;

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
	double				fov;
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
	double				radius;
}						t_sphere;

typedef struct s_plane
{
	t_vec3				point;
	t_vec3				dir;
	t_vec3				u_axis;
	t_vec3				v_axis;
	double				scale;
}						t_plane;

typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				axis;
	double				radius;
	double				height;
}						t_cylinder;

typedef union u_shape
{
	t_sphere			sp;
	t_plane				pl;
	t_cylinder			cy;
}						t_shape;

typedef struct s_object
{
	t_type				type;
	t_vec3				center;
	t_vec3				color;
	t_shape				shape;
	int					has_texture;
	char				*tex_path;
	t_xpm				texture;
	struct s_object		*next;
}						t_object;

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
	t_object			*objects;
	int					amb_count;
	int					light_count;
}						t_scene;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	t_img				img;
	t_scene				scene;
	t_tex_cache			*tex_cache;
}						t_data;

typedef struct s_quad_eq
{
	double				delta;
	double				t1;
	double				t2;
	double				a;
	double				b;
	double				c;
}						t_quad_eq;

typedef struct s_hit
{
	double				t;
	t_vec3				hit_point;
	t_vec3				normal;
	t_object			*obj;
	t_normal			normal_type;
}						t_hit;

typedef struct s_thread_data
{
	struct s_data		*data;
	int					start_y;
	int					end_y;
	int					cam_in;
}						t_thread_data;

#endif