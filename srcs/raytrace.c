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


t_vec3	transform_ndc_to_worldspace(t_vec3 *ndc, t_coord_sys *camera)
{
	t_vec3	world_dir;

	world_dir.x = ndc->x * camera->right.x + ndc->y * camera->up.x + ndc->z * camera->forward.x;
	world_dir.y = ndc->x * camera->right.y + ndc->y * camera->up.y + ndc->z * camera->forward.y;
	world_dir.z = ndc->x * camera->right.z + ndc->y * camera->up.z + ndc->z * camera->forward.z;
	normalize(world_dir);
	return (world_dir);
}
void	calc_camera_coord_sys(t_camera *camera)
{
	t_vec3 world_up;
	
	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	if (check_equal(&world_up, &camera->coord_sys.forward))
	{
		world_up.y = 0;
		world_up.z = 1;
	}
	camera->coord_sys.right = normalize(cross(world_up, camera->coord_sys.forward));
	camera->coord_sys.up = normalize(cross(camera->coord_sys.right, camera->coord_sys.forward));
	camera->coord_sys.forward = camera->orientation;
}

t_vec3	get_ray_dir(t_camera *camera, int x, int y)
{
	t_vec3	ndc_dir;
	t_vec3	world_dir;
	double	aspect_ratio;

	aspect_ratio = WIN_WIDTH / WIN_HEIGHT;
	ndc_dir.x = ((((x + 0.5) / WIN_WIDTH) * 2) - 1) * aspect_ratio;
	ndc_dir.y = 1 - (((y + 0.5) / WIN_HEIGHT) * 2);

	ndc_dir.x *= tan(camera->fov / 2 * PI / 180);
	ndc_dir.y *= tan(camera->fov / 2 * PI / 180);
	ndc_dir.z = -1;

	calc_camera_coord_sys(camera);
	world_dir = transform_ndc_to_worldspace(&ndc_dir, &camera->coord_sys);

	return (world_dir);
}

void	raytrace(t_scene *scene)
{
	double	aspect_ratio;
	t_ray	ray;
	int		i;
	int		j;

	calculate_image_plane(scene);
	aspect_ratio = WIN_WIDTH / WIN_HEIGHT;
	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			ray.origin = scene->camera.pos;
			ray.direction = get_ray_dir(&scene->camera, i, j);
		}
	}
}
