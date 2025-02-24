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

void	calculate_image_plane(t_scene *scene)
{
	t_vector3 world_up;
	t_vector3 world_forward;
	t_vector3 *camera_right;
	t_vector3 *camera_up;
	
	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	world_forward.x = 0;
	world_forward.y = 1;
	world_forward.z = 0;
	if (!check_equal(&world_up, &scene->camera.forward))
		camera_right = cross(&world_up, &scene->camera.forward);
	else
		camera_right = cross(&world_forward, &scene->camera.forward);
	camera_up = cross(&camera_right, &scene->camera.forward);
	normalize(camera_right);
	normalize(camera_up);
	set_equal(&scene->camera.right, camera_right);
	set_equal(&scene->camera.up, camera_up);
	free(camera_right);
	free(camera_up);
}

void	cast_ray(t_scene *scene, int x, int y)
{
	t_vector3 ndc;
	double	aspect_ratio;

	aspect_ratio = WIN_WIDTH / WIN_HEIGHT;
	ndc.x = ((((x + 0.5) / WIN_WIDTH) * 2) - 1) * aspect_ratio;
	ndc.y = 1 - (((x + 0.5) / WIN_HEIGHT) * 2);

	ndc.x *= tan(scene->camera.fov / 2 * PI / 180);
	ndc.y *= tan(scene->camera.fov / 2 * PI / 180);
	ndc.z = -1;
}

void	raytrace(t_scene *scene)
{
	double	aspect_ratio;
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
			cast_ray(scene, i, j);
		}
	}
}