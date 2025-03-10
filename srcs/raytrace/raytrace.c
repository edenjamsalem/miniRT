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

t_rgb	get_colour(int x, int y, t_mlx *mlx, t_vec2 offset)
{
	t_ray	ray;
	t_rgb	colour;

	ray.origin = mlx->scene.camera.pos;
	ray.direction = calc_ray_dir(&mlx->scene.camera, x, y, offset);
	ray.intsec = find_intersection(&ray, mlx->scene.objs->content);
	if (ray.intsec.obj)
		return ((t_rgb){0, 0, 0});
	cast_shadow_rays(&ray.intsec, &mlx->scene, mlx);
	colour = blinn_phong(&mlx->scene, &ray.intsec, scale(ray.direction, -1));
	return (colour);
}

void	raytrace(t_mlx *mlx)
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
			while (++k < mlx->scene.consts.rpp)
				colours[k] = get_colour(j, i, mlx, mlx->scene.consts.pixel_offsets[k]);

			final_colour = rgb_average(colours, mlx->scene.consts.rpp);
			put_pixel(&mlx->img, &(t_vec2){j, i}, &final_colour);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	printf("FINISHED RAYTRACE\n");
}
