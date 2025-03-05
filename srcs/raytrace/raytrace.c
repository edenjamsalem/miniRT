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
#include <time.h>

t_vec3	transform_ndc_to_worldspace(t_vec3 *ndc, t_basis *cam)
{
	t_vec3	world_dir;

	world_dir.x = ndc->x * cam->right.x + ndc->y * cam->up.x + ndc->z * cam->forward.x;
	world_dir.y = ndc->x * cam->right.y + ndc->y * cam->up.y + ndc->z * cam->forward.y;
	world_dir.z = ndc->x * cam->right.z + ndc->y * cam->up.z + ndc->z * cam->forward.z;
	return(world_dir);
}

t_vec3	calc_ray_dir(t_camera *camera, int x, int y, t_vec2 *offset)
{
	t_vec3	ndc_dir;
	t_vec3	world_dir;

	ndc_dir.x = ((2.0 * ((x + 0.5) / WIN_WIDTH)) - 1) * camera->aspect_ratio;
	ndc_dir.y = 1 -  (2.0 * ((y + 0.5) / WIN_HEIGHT));
	
	ndc_dir.x *= camera->fov_tan;
	ndc_dir.y *= camera->fov_tan;
	ndc_dir.z = -1;

	world_dir = transform_ndc_to_worldspace(&ndc_dir, &camera->basis);
	return (normalize(world_dir));
}

void	init_offset(t_vec2 *offset)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			offset->x = 0.25 * i;
			offset->y = 0.25 * j;
		}
	}
}

void	render_pixel(int x, int y, t_mlx *mlx)
{
	t_rgb		colour[16];
	t_ray		ray[16];
	t_vec2		offset[16];
	int			i;

	init_offset(offset);
	i = 0;
	while (i < 16)
	{
		ray[i].origin = mlx->scene.camera.pos;
		ray[i].direction = calc_ray_dir(&mlx->scene.camera, x, y);
		ray[i].intersection = find_intersection(ray, mlx->scene.objs->content);
		if (ray->intersection.obj)
		{
		  	cast_shadow_rays(&ray->intersection, &mlx->scene);
			colour[i] = blinn_phong(&mlx->scene, &ray->intersection, scale(ray->direction, -1));
		}
	}
	put_pixel(&mlx->img, &(t_vec3){x, y, 0}, &colour);
}

void	raytrace(t_scene *scene, t_mlx *mlx)
{
	int			i;
	int			j;

	i = 0;
	while (i < WIN_HEIGHT - 1)
	{
		j = 0;
		while (j < WIN_WIDTH - 1)
		{ 
			render_pixel(&ray, j, i, mlx);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	printf("FINISHED RAYTRACE\n");
}
