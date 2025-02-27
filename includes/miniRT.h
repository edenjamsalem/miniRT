#include "../libs/minilibx-linux/mlx.h"
#include "../libs/Libft/libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//      WINDOW SIZE
#define WIN_WIDTH        1200
#define WIN_HEIGHT      800

//      EVENT MACROS
#define KEY_PRS_EVT     2
#define KEY_REL_EVT     3
#define BTN_PRS_EVT     4
#define BTN_REL_EVT     5
#define DESTROY_EVT     17

// KEYSYMS
#define ESC_KEY                 0xff1b
#define A_KEY                   0x0061
#define S_KEY                   0x0073
#define D_KEY                   0x0064
#define W_KEY                   0x0077
#define Q_KEY                   0x0071
#define E_KEY                   0x0065
#define UP_KEY                  0xff52
#define DOWN_KEY                0xff54
#define LEFT_KEY                0xff51
#define RIGHT_KEY               0xff53
#define SCROLL_UP               4
#define SCROLL_DOWN             5

#define PI 3.14159265358979323846

typedef enum e_err
{
    LINE_ARG_COUNT,
    ARG_OUT_OF_RANGE,
    DUPLICATE,
    MALLOC,
}				t_err;

typedef enum e_shape
{
    SPHERE,
    PLANE,
    CYLINDER,
    NONE,
}				t_shape;

typedef struct s_rgb
{
//    unsigned char   t;
    unsigned char   r;
    unsigned char   g;
    unsigned char   b;
}				t_rgb;

typedef struct s_vec3
{
    double          x;
    double          y;
    double          z;
}				t_vec3;

typedef struct s_basis
{
    t_vec3  right;
    t_vec3  up;
    t_vec3  forward;
}           t_basis;

typedef struct s_light
{
	t_vec3	    pos;
	float		brightness;
	t_rgb	    colour;
} 				t_light;

typedef struct s_camera
{
	t_vec3	    pos;
	t_vec3	    orientation;
	t_basis     basis;
    int		    fov;
    double		fov_tan; // to optimise ray trace
	double		aspect_ratio;
} 				t_camera;

typedef struct s_scene
{
	t_light		ambient_light;
	t_light		light_src;
	t_camera	camera;
    t_arrlst    *objs;
	t_basis     world;
	t_vec3		world_step_x;
	t_vec3		world_step_y;
}				t_scene;

typedef struct s_sphere
{
    t_shape     shape;
    t_vec3	    center;
    double		diameter;
    t_rgb		colour;
}				t_sphere;

typedef struct s_plane
{
    t_shape     shape;
    t_vec3	    point;
    t_vec3	    normal;
    t_rgb		colour;
}				t_plane;

typedef struct s_cylinder
{
    t_shape     shape;
    t_vec3	    center;
    t_vec3	    normal;
    double		diameter;
    double		height;
    t_rgb		colour;
}				t_cylinder;

typedef struct s_intersection
{
    t_vec3  pos;
    t_vec3  normal;
    t_rgb   colour;
    t_shape shape;
}              t_intsec;

typedef struct s_ray
{
    t_vec3      origin;
    t_vec3      direction;
    t_intsec    intersection;
}           t_ray;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_img		img;
    t_scene     scene;
}				t_mlx;

//	PARSE

void	get_ambient_light_data(t_scene *scene, char **data, int line_nbr);

void	get_camera_data(t_scene *scene, char **data, int line_nbr);

void	get_light_src_data(t_scene *scene, char **data, int line_nbr);

void	extract_data(t_scene *scene, char **data, int line_nbr);

void    parse(char *file, t_scene *scene);

void	perror_exit(t_err err, int line_nbr, char **data, int i, t_scene *scene);

void	assign_vector(t_vec3 *vector, char *data);

bool	in_range(double value, double lower, double higher);

bool	assign_rgb(t_rgb *rgb, char *data);

bool	vector_in_range(t_vec3 *vector, double lower, double upper);

void	get_sphere_data(t_scene *scene, char **data, int line_nbr);

void	get_plane_data(t_scene *scene, char **data, int line_nbr);

void	get_cylinder_data(t_scene *scene, char **data, int line_nbr);

void	init_scene_basis(t_scene *scene);

void	init_camera_basis(t_camera *camera, t_basis *world);

// MLX

int     key_event(int keysym, t_mlx *mlx);

int	    close_window(t_mlx *mlx);

void	free_mem(t_mlx *mlx);

void	init_mlx_data(t_mlx *mlx);

void	init_img_data(t_img *img, t_mlx *mlx);

void	put_pixel(t_img *img, t_vec3 *pos, t_rgb *colour);

// VECTOR

t_vec3    add(t_vec3 a, t_vec3 b);

t_vec3    sub(t_vec3 a, t_vec3 b);

t_vec3    mult(t_vec3 a, double t);

double	dot(t_vec3 a, t_vec3 b);

double	magnitude(t_vec3 a);

t_vec3	cross(t_vec3 a, t_vec3 b);

t_vec3	normalize(t_vec3 a);

bool    check_equal(t_vec3 *a, t_vec3 *b);

void	print_vector(t_vec3 a);


// RAY TRACE

t_intsec	find_intersection(t_ray *ray, void **objs);

t_intsec	check_plane_intersection(t_ray *ray, t_plane *plane);

void	raytrace(t_scene *scene, t_mlx *mlx);
