/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:22:27 by eamsalem          #+#    #+#             */
/*   Updated: 2025/05/28 08:42:35 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minilibx-linux/mlx.h"
#include "../libs/Libft/libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

//	  WINDOW SIZE
#define WIN_WIDTH		1200
#define WIN_HEIGHT	  800

//	  EVENT MACROS
#define KEY_PRS_EVT	 2
#define KEY_REL_EVT	 3
#define BTN_PRS_EVT	 4
#define BTN_REL_EVT	 5
#define DESTROY_EVT	 17

// KEYSYMS
#define ESC_KEY				 0xff1b
#define A_KEY				   0x0061
#define S_KEY				   0x0073
#define D_KEY				   0x0064
#define W_KEY				   0x0077
#define Q_KEY				   0x0071
#define E_KEY				   0x0065
#define UP_KEY				  0xff52
#define DOWN_KEY				0xff54
#define LEFT_KEY				0xff51
#define RIGHT_KEY			   0xff53
#define SCROLL_UP			   4
#define SCROLL_DOWN			 5

#define PI 3.14159265358979323846

typedef enum e_err
{
	LINE_ARG_COUNT,
	ARG_OUT_OF_RANGE,
	DUPLICATE,
	VEC_COUNT,
	RGB_COUNT,
	MALLOC,
	_FILE,
}				t_err;

typedef enum e_shape
{
	NONE,
	SP,
	PL,
	CY,
}				t_shape;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_rgb;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct t_pixel
{
	double	x;
	double	y;
	t_rgb	colour;
}	t_pixel;

typedef struct s_basis
{
	t_vec3	right;
	t_vec3	up;
	t_vec3	fwd;
}			t_basis;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
}		t_quadratic;

typedef struct s_light
{
	t_vec3	center;
	double	radius;
	float	brightness;
	t_rgb	colour;
	t_vec3	dir;
	double	visibility;
	t_vec3	rand_positions[128];
}			t_light;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	orientation;
	t_basis	basis;
	int		fov;
	double	fov_tan;
	double	aspect_r;
}			t_camera;

typedef struct s_consts
{
	t_vec2	px_offset[64];
	int		rpp;
	int		shadow_rpp;
	t_basis	world;
}			t_consts;

typedef struct s_scene
{
	t_camera	camera;
	t_light		ambient_light;
	t_arrlst	*lights;
	t_arrlst	*objs;
	t_consts	consts;
}			t_scene;

typedef struct s_surf
{
	double	k_ambient;
	double	k_diffuse;
	double	k_specular;
	double	exp;
}			t_surf;

typedef struct s_sp
{
	t_shape	shape;
	t_vec3	center;
	double	diameter;
	double	radius;
	t_rgb	colour;
	t_surf	surf;
	bool	camera_inside;
}			t_sp;

typedef struct s_pl
{
	t_shape	shape;
	t_vec3	point;
	t_vec3	normal;
	t_rgb	colour;
	t_surf	surf;
}			t_pl;

typedef struct s_cy
{
	t_shape	shape;
	t_vec3	center;
	t_vec3	axis;
	t_vec3	top_center;
	t_vec3	bottom_center;
	double	diameter;
	double	radius;
	double	height;
	double	top_h;
	double	bottom_h;
	double	rad_sqr;
	t_rgb	colour;
	t_surf	surf;
	bool	camera_inside;
	int		intsec_count;
}				t_cy;

typedef struct s_intersection
{
	t_vec3	pos;
	t_vec3	normal;
	t_rgb	colour;
	void	*obj;
	double	t;
	bool	in_shadow;
	t_surf	surf;
}			t_intsec;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		dir;
	t_intsec	intsec;
}			t_ray;

typedef struct s_shadow
{
	t_ray	ray;
	t_basis	basis;
}			t_shadow;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	img;
	t_scene	scene;
}			t_mlx;

typedef struct s_parse
{
	int		line_num;
	char	**data;
	char	*arg;
	t_scene	*scene;
}			t_parse;

//	PARSE

void			get_ambient_light_data(t_parse *parse, t_scene *scene);

void			get_camera_data(t_parse *parse, t_scene *scene);

void			get_light_data(t_parse *parse, t_scene *scene);

void			extract_data(t_parse *parse, t_scene *scene);

void			parse(char *file, t_scene *scene);

void			perror_exit(t_err err, t_parse *parse, int i);

bool			assign_vector(t_vec3 *vector, char *data);

bool			assign_material(t_surf *material, char *data);

bool			in_range(double value, double lower, double higher);

bool			assign_rgb(t_rgb *rgb, char *data);

bool			vector_in_range(t_vec3 *vector, double lower, double upper);

void			get_sp_data(t_parse *parse, t_scene *scene);

void			get_pl_data(t_parse *parse, t_scene *scene);

void			get_cy_data(t_parse *parse, t_scene *scene);

void			assign_default_material(t_surf *surf);

bool			rgb_in_range(int rgb[3]);

bool			invalid_duplicate(t_parse *parse);

bool			invalid_extension(char *file);

// MLX

int				key_event(int keysym, t_mlx *mlx);

int				close_window(t_mlx *mlx);

void			free_mem(t_mlx *mlx);

void			put_pixel(t_pixel *pixel, t_img *img);

// VECTOR

t_vec3			add(t_vec3 a, t_vec3 b);

t_vec3			sub(t_vec3 a, t_vec3 b);

t_vec3			scale(t_vec3 a, double t);

double			dot(t_vec3 a, t_vec3 b);

double			magnitude(t_vec3 a);

t_vec3			cross(t_vec3 a, t_vec3 b);

t_vec3			normalize(t_vec3 a);

void			print_vector(t_vec3 a);

t_vec3			transform_basis(t_vec3 *ndc, t_basis *local);

// RAY TRACE

void			render_scene(t_mlx *mlx);

void			cast_shadow_rays(t_intsec *intsec, t_scene *scene);

void			gen_rand_offsets(t_light *light, t_basis *shadow, \
															t_consts *consts);

t_rgb			blinn_phong(t_scene *scene, t_intsec *intsec, t_vec3 view_dir);

// INTERSECTIONS

double			get_pl_t(t_ray *ray, t_pl *pl);

void			get_pl_intsec_data(t_ray *ray, t_pl *pl, t_intsec *intsec);

double			get_sp_t(t_ray *ray, t_sp *sp);

void			get_sp_intsec_data(t_ray *ray, t_sp *sp, t_intsec *intsec);

double			get_curved_t(t_ray *ray, t_cy *cy);

void			get_cy_intsec_data(t_ray *ray, t_cy *cy, t_intsec *intsec);

void			check_camera_inside_objs(void **objs, t_camera *camera);

t_intsec		find_intersection(t_ray *ray, void **objs);

bool			camera_in_sp(t_sp *sp, t_camera *camera);

bool			camera_in_cy(t_cy *cy, t_camera *camera);

// UTILS

unsigned int	rgb_to_int(t_rgb rgb);

t_rgb			rgb_add(t_rgb a, t_rgb b);

t_rgb			rgb_sub(t_rgb a, t_rgb b);

t_rgb			rgb_scale(t_rgb a, double t);

t_rgb			rgb_mult(t_rgb a, t_rgb b);

t_rgb			rgb_average(t_rgb *colours, int count);

int				max(int a, int b);

int				min(int a, int b);

void			print_rgb(t_rgb rgb);

double			calc_time_diff(struct timeval *start, struct timeval *end);

// INIT

void			init_pixel_offsets(t_consts *ssaa);

void			init_world_basis(t_basis *world);

void			calc_local_basis(t_basis *local, t_vec3 fwd, t_basis *world);

void			init_mlx_data(t_mlx *mlx);

void			init_img_data(t_img *img, t_mlx *mlx);

void			init_intsec(t_intsec *intersection);

void			init_project(t_mlx *mlx, t_scene *scene, t_camera *camera);
