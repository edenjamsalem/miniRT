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

	// print_vector(*ndc);
	// print_vector(camera->up);
	// print_vector(camera->right);
	// print_vector(camera->forward);
	// printf("\n");
	// sleep(1);

	world_dir.x = ndc->x * cam->right.x + ndc->y * cam->up.x + ndc->z * cam->forward.x;
	world_dir.y = ndc->x * cam->right.y + ndc->y * cam->up.y + ndc->z * cam->forward.y;
	world_dir.z = ndc->x * cam->right.z + ndc->y * cam->up.z + ndc->z * cam->forward.z;
	return(normalize(world_dir));
}

t_vec3	calc_initial_ray_dir(t_camera *camera)
{
	t_vec3	ndc_dir;
	t_vec3	world_dir;

	ndc_dir.x = ((1 / WIN_WIDTH * 4.0) - 1) * camera->aspect_ratio;
	ndc_dir.y = 1 - (1 / WIN_HEIGHT * 4.0);
	
	ndc_dir.x *= camera->fov_tan;
	ndc_dir.y *= camera->fov_tan;
	ndc_dir.z = -1;
	
	world_dir = transform_ndc_to_worldspace(&ndc_dir, &camera->basis);
	return (world_dir);
}

void	calc_world_step(t_scene *scene, t_camera *camera)
{
	double ndc_step_x;	
	double ndc_step_y;	
	
	ndc_step_x = (2.0 / WIN_WIDTH) * camera->aspect_ratio * camera->fov_tan;
	ndc_step_y = -(2.0 / WIN_HEIGHT) * camera->fov_tan;

	scene->world_step_x = scale(camera->basis.right, ndc_step_x);
	scene->world_step_y = scale(camera->basis.up, ndc_step_y);
}

void	raytrace(t_scene *scene, t_mlx *mlx)
{
	t_ray		initial_ray;
	t_ray		ray;
	t_intsec	intersection;
	int			i;
	int			j;
	
	initial_ray.origin = scene->camera.pos;
	initial_ray.direction = calc_initial_ray_dir(&scene->camera);
	calc_world_step(scene, &scene->camera);
	ray = initial_ray;

	i = 0;
	while (i < WIN_HEIGHT - 1)
	{
		j = 0;
		while (j < WIN_WIDTH - 1)
		{ 
			intersection = find_intersection(&ray, scene->objs->content);
			if (intersection.obj)
			  	intersection.in_shadow = cast_shadow_ray(&intersection, scene);
			// printf("exists = %d\n", intersection.exists);	
			// printf("in shadow = %d\n", intersection.in_shadow);	
			if (!intersection.in_shadow)
				put_pixel(&mlx->img, &(t_vec3){j, i, 0}, &intersection.colour);
			
			ray.direction = normalize(add(ray.direction, scene->world_step_x));
			j++;
		}
		ray.direction.x = initial_ray.direction.x;
		ray.direction = normalize(add(ray.direction, scene->world_step_y));
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	printf("FINISHED RAYTRACE\n");
}
