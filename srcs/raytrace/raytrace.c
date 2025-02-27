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

t_vec3	transform_ndc_to_worldspace(t_vec3 *ndc, t_basis *camera)
{
	t_vec3	world_dir;

	// print_vector(*ndc);
	// print_vector(camera->up);
	// print_vector(camera->right);
	// print_vector(camera->forward);

	// printf("\n");

	// sleep(1);

	world_dir.x = ndc->x * camera->right.x + ndc->y * camera->up.x + ndc->z * camera->forward.x;
	world_dir.y = ndc->x * camera->right.y + ndc->y * camera->up.y + ndc->z * camera->forward.y;
	world_dir.z = ndc->x * camera->right.z + ndc->y * camera->up.z + ndc->z * camera->forward.z;
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

	scene->world_step_x = mult(camera->basis.right, ndc_step_x);
	scene->world_step_y = mult(camera->basis.up, ndc_step_y);
}

void	raytrace(t_scene *scene, t_mlx *mlx)
{
	t_ray		initial_ray;
//	t_ray		shadow_ray;
	t_ray		ray;
	t_intsec	intsec;
	int			i;
	int			j;
	
	scene->camera.fov_tan = tan(scene->camera.fov / 2 * PI / 180);
	scene->camera.aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	
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
			intsec = find_intersection(&ray, scene->objs->content);
			put_pixel(&mlx->img, &(t_vec3){j, i, 0}, &intsec.colour);
			ray.direction = normalize(add(ray.direction, scene->world_step_x));
			j++;
		}
		ray.direction.x = initial_ray.direction.x;
		ray.direction = normalize(add(ray.direction, scene->world_step_y));
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
//	printf("FINISHED RAYTRACE\n");
}
