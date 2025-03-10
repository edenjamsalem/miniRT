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

t_vec3	transform_local_to_world(t_vec3 *ndc, t_basis *local)
{
	t_vec3	world_dir;

	world_dir.x = ndc->x * local->right.x + ndc->y * local->up.x + ndc->z * local->forward.x;
	world_dir.y = ndc->x * local->right.y + ndc->y * local->up.y + ndc->z * local->forward.y;
	world_dir.z = ndc->x * local->right.z + ndc->y * local->up.z + ndc->z * local->forward.z;
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

	world_dir = transform_local_to_world(&ndc_dir, &camera->basis);
	return (normalize(world_dir));
}

t_rgb	raytrace(int x, int y, t_scene *scene)
{
	t_ray	ray;
	t_rgb		colours[64];
	t_rgb		final_colour;
	int			i;

	i = -1;
	ray.origin = scene->camera.pos;
	while (++i < scene->consts.rpp)
	{
		ray.direction = calc_ray_dir(&scene->camera, x, y, scene->consts.pixel_offsets[i]);
		ray.intsec = find_intersection(&ray, scene->objs->content);
		if (!ray.intsec.obj)
			colours[i] = (t_rgb){0, 0, 0};
		else
		{
			cast_shadow_rays(&ray.intsec, scene);
			colours[i] = blinn_phong(scene, &ray.intsec, scale(ray.direction, -1));
		}
	}
	final_colour = rgb_average(colours, scene->consts.rpp);
	return (final_colour);
}

void	render_pixels(t_mlx *mlx)
{
	int		i;
	int		j;
	t_rgb	colour;
	t_pixel	pixel;

	i = -1;
	while (++i < WIN_HEIGHT - 1)
	{
		j = -1;
		while (++j < WIN_WIDTH - 1)
		{ 
			colour = raytrace(j, i, &mlx->scene);
			pixel = (t_pixel){j, i, colour};
			put_pixel(&pixel, &mlx->img);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	printf("FINISHED RAYTRACE\n");
}
