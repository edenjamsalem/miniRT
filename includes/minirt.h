#include "mlx_linux/mlx.h"
#include "../libft/libft.h"
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

typedef struct s_colour
{
    unsigned char   t;
    unsigned char   r;
    unsigned char   g;
    unsigned char   b;
}				t_colour;

typedef struct s_coord
{
    double          x;
    double          y;
    double          z;
    t_colour        colour;
}				t_coord;

typedef struct s_light
{
	t_coord		pos;
	float		light_ratio;
	t_colour	colour;
} 				t_light;

typedef struct s_camera
{
	t_coord	pos;
    t_coord	oriention;
	int		fov;
} 				t_camera;

typedef struct s_scene
{
	t_light		ambient;
	t_light		light_source;
	t_camera	camera;
}				t_scene;
