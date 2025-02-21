#include "mlx_linux/mlx.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//      WINDOW SIZE
#define WIN_LEN         1200
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
}				t_shape;

typedef struct s_rgb
{
//    unsigned char   t;
    unsigned char   r;
    unsigned char   g;
    unsigned char   b;
}				t_rgb;

typedef struct s_vector3
{
    double          x;
    double          y;
    double          z;
//    t_rgb        colour;
}				t_vector3;

typedef struct s_light
{
	t_vector3	pos;
	float		brightness;
	t_rgb	    colour;
} 				t_light;

typedef struct s_camera
{
	t_vector3	pos;
    t_vector3	oriention;
	int		    fov;
} 				t_camera;

typedef struct s_scene
{
	t_light		ambient_light;
	t_light		light_src;
	t_camera	camera;
    t_arrlst    *objs;
}				t_scene;

typedef struct s_sphere
{
    t_shape     shape;
    t_vector3	center;
    double		diameter;
    t_rgb		colour;
}				t_sphere;

typedef struct s_plane
{
    t_shape     shape;
    t_vector3	point;
    t_vector3	normal;
    t_rgb		colour;
}				t_plane;

typedef struct s_cylinder
{
    t_shape     shape;
    t_vector3	center;
    t_vector3	normal;
    double		diameter;
    double		height;
    t_rgb		colour;
}				t_cylinder;

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

bool    parse(char *file, t_scene *scene);

void	perror_exit(t_err err, int line_nbr, char **data, int i, t_scene *scene);

void	assign_vector(t_vector3 *vector, char *data);

bool	in_range(double value, double lower, double higher);

bool	assign_rgb(t_rgb *rgb, char *data);

bool	vector_in_range(t_vector3 *vector, double lower, double upper);

void	get_sphere_data(t_scene *scene, char **data, int line_nbr);

void	get_plane_data(t_scene *scene, char **data, int line_nbr);

void	get_cylinder_data(t_scene *scene, char **data, int line_nbr);


// MLX

int     key_event(int keysym, t_mlx *mlx);

int	    close_window(t_mlx *mlx);

void	free_mem(t_mlx *mlx);
