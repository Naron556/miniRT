/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:44:01 by yamohamm          #+#    #+#             */
/*   Updated: 2026/03/13 11:32:10 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "libmlx/mlx.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

# define ESC_KEY_MAC 53
# define ESC_KEY_LINUX 65307
# define WHITE 0x00FFFFFF
# define BLACK 0x0000000
# define RED 0xFF0000
# define PI 3.141592653589793
# define WIDTH (double)800
# define HEIGHT (double)600
# define ASPECT (WIDTH / HEIGHT)
# define THREADS 8

# define ERR_ARGS "Error\nWrong number of arguments\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_MEM "Error\nMemory allocation failed\n"
# define ERR_VAL "Error\nInvalid value in scene file\n"
# define ERR_DUP "Error\nDuplicate scene element (A, C,)\n"

/*---------- /src/math ----------*/

t_vec3		vec_scale(t_vec3 vec, double scalar);
double		vec_dot(t_vec3 first, t_vec3 sec);
t_vec3		vec_sub(t_vec3 first, t_vec3 sec);
t_vec3		vec_add(t_vec3 first, t_vec3 sec);
double		vec_len(t_vec3 vec);
t_vec3		vec_cross(t_vec3 first, t_vec3 second);
t_vec3		vec_normalize(t_vec3 vec);
void		cam_vec(t_camera *cam);
t_vec3		map_pixel(double i, double j, t_camera cam);
double		cnv_to_rad(double angle);
t_quad_eq	sp_intsec(t_ray ray, t_object sphere);
double		pl_intsec(t_ray ray, t_object sp);
t_vec3		get_normal(t_ray ray, t_hit hit);
double		obj_dist(t_object *obj, t_ray ray, t_hit *hit);
t_hit		closest_hit(t_object *objs, t_ray ray);
t_quad_eq	cy_quad(t_ray ray, t_object cy);
int			t_in_height(t_ray ray, t_object cy, double t);
t_quad_eq	cy_intsec(t_ray ray, t_object cy, t_hit *hit);
double		intensity_on_hp(t_scene scene, t_hit hit);
int			hp_in_shadow(t_hit hit, t_object *objs, t_light light);
double		cap_intsec(t_ray ray, t_vec3 axis, t_vec3 center, double radius);
void		cy_normal_type(t_hit *hit, t_quad_eq *eq, double t1, double t2);
t_vec3		cy_normal(t_hit hit);

void		init_mlx(t_data *data);
void		setup_hooks(t_data *data);
int			close_window(t_data *data);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			key_hook(int keycode, t_data *data);

/*---------- parse_free.c ----------*/
void		free_scene(t_scene *scene);
void	error_exit_parse(t_scene *scene, char **tokens, char *msg); // NEW

/*---------- parse_utils.c ----------*/
void		free_tokens(char **tokens);
int			count_tokens(char **tokens);
double		ft_atof(const char *str);
t_vec3	parse_vec3(char *str, t_scene *scene, char **tokens);  // UPDATED
t_vec3	parse_color(char *str, t_scene *scene, char **tokens); // UPDATED

/*---------- parse_elements.c ----------*/
void		parse_ambient(t_scene *scene, char **tokens);
void		parse_camera(t_scene *scene, char **tokens);
void		parse_light(t_scene *scene, char **tokens);

/*---------- parse_shapes.c ----------*/
void		add_object(t_scene *scene, t_object *new_obj);
void		parse_sphere(t_scene *scene, char **tokens);
void		parse_plane(t_scene *scene, char **tokens);
void		parse_cylinder(t_scene *scene, char **tokens);

/*---------- parse.c ----------*/
void		parse_line(t_scene *scene, char *line);
void		init_scene(t_scene *scene);
void		parse_file(t_data *data, char *filename);

/*---------- render ----------*/
void		render_scene(t_data *data);
t_vec3		apply_texture(t_hit *hit);

void		load_object_textures(t_data *data);
int			is_cam_inside(t_scene *scene);


double		specular(t_hit hit, t_vec3 hit_to_light, t_vec3 cam_point, double ratio);
int			hp_in_shadow(t_hit hit, t_object *objs, t_light light);
double		intensity_on_hp(t_scene scene, t_hit hit);


#endif
