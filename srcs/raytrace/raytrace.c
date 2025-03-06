/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:43:09 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/24 16:00:26by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec3	transform_ndc_to_worldspace(t_vec3 *ndc, t_basis *cam)
{
	t_vec3	world_dir;

	world_dir.x = ndc->x * cam->right.x + ndc->y * cam->up.x + ndc->z * cam->forward.x;
	world_dir.y = ndc->x * cam->right.y + ndc->y * cam->up.y + ndc->z * cam->forward.y;
	world_dir.z = ndc->x * cam->right.z + ndc->y * cam->up.z + ndc->z * cam->forward.z;
	return(world_dir);
}

t_vec3	calc_ray_dir(t_camera *camera, int x, int y, t_vec2 offset)
{
	t_vec3	ndc_dir;
	t_vec3	world_dir;

	ndc_dir.x = ((2.0 * ((x + offset.x) / WIN_WIDTH)) - 1) * camera->aspect_ratio;
	ndc_dir.y = 1 -  (2.0 * ((y + offset.y) / WIN_HEIGHT));
	
	ndc_dir.x *= camera->fov_tan;
	ndc_dir.y *= camera->fov_tan;
	ndc_dir.z = -1;

	world_dir = transform_ndc_to_worldspace(&ndc_dir, &camera->basis);
	return (normalize(world_dir));
}

static t_rgb	rgb_average(t_rgb colours[16], int count)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < count)
	{
		r += colours[i].r;
		g += colours[i].g;
		b += colours[i].b;
		i++;
	}
	r = round(r / count);
	g = round(g / count);
	b = round(b / count);
	return ((t_rgb){r, g, b});
}

bool	all_equal(t_rgb *colours, int count)
{
	int i;

	i = 0;
	while (i < count - 1)
	{
		if (!rgb_equal(colours[i], colours[i + 1]))
			return (false);
		i++;
	}
	return (true);
}

t_rgb	get_colour(int x, int y, t_mlx *mlx, t_vec2 offset)
{
	t_ray	ray;
	t_rgb	colour;

	ray.origin = mlx->scene.camera.pos;
	ray.direction = calc_ray_dir(&mlx->scene.camera, x, y, offset);
	ray.intersection = find_intersection(&ray, mlx->scene.objs->content);
	if (!ray.intersection.obj)
		return ((t_rgb){0, 0, 0});
	cast_shadow_rays(&ray.intersection, &mlx->scene);
	colour = blinn_phong(&mlx->scene, &ray.intersection, scale(ray.direction, -1));
	return (colour);
}

void	raytrace(t_mlx *mlx, t_ssaa *ssaa)
{
	int			i;
	int			j;
	int			k;
	t_rgb		colours[64];
	t_rgb		final_colour;

	i = -1;
	while (++i < WIN_HEIGHT - 1)
	{
		j = -1;
		while (++j < WIN_WIDTH - 1)
		{ 
			k = -1;
			while (++k < mlx->ssaa.rpp)
				colours[k] = get_colour(j, i, mlx, ssaa->offset[k]);

			final_colour = rgb_average(colours, ssaa->rpp);
			put_pixel(&mlx->img, &(t_vec3){j, i, 0}, &final_colour);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	printf("FINISHED RAYTRACE\n");
}
