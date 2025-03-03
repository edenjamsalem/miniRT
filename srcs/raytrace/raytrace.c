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

t_vec3	calc_ray_dir(t_camera *camera, int x, int y)
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

void	raytrace(t_scene *scene, t_mlx *mlx)
{
	t_ray		ray;
	int			i;
	int			j;
	t_rgb		colour;
	struct timeval	start;
	struct timeval	end;
	
	gettimeofday(&start, NULL);
	ray.origin = scene->camera.pos;
	i = 0;
	while (i < WIN_HEIGHT - 1)
	{
		j = 0;
		while (j < WIN_WIDTH - 1)
		{ 
			ray.direction = calc_ray_dir(&scene->camera, j, i);
			ray.intersection = find_intersection(&ray, scene->objs->content);
			if (ray.intersection.obj)
			{
			  	ray.intersection.in_shadow = cast_shadow_ray(&ray.intersection, scene);
				colour = blinn_phong(scene, &ray.intersection, scale(ray.direction, -1));
				put_pixel(&mlx->img, &(t_vec3){j, i, 0}, &colour);
			}	
			j++;
		}
		i++;
	}
	gettimeofday(&end, NULL);
	printf("time = %f\n", calc_time_diff(&start, &end) / 1000);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	printf("FINISHED RAYTRACE\n");
}

