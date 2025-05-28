/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:06:34 by eamsalem          #+#    #+#             */
/*   Updated: 2025/05/28 09:29:11 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec3	get_ray_dir(t_camera *camera, int x, int y, t_vec2 offset)
{
	t_vec3	ndc_dir;
	t_vec3	world_dir;

	ndc_dir.x = ((2.0 * ((x + offset.x) / WIN_WIDTH)) - 1) * camera->aspect_r;
	ndc_dir.y = 1 - (2.0 * ((y + offset.y) / WIN_HEIGHT));
	ndc_dir.x *= camera->fov_tan;
	ndc_dir.y *= camera->fov_tan;
	ndc_dir.z = 1;
	world_dir = transform_basis(&ndc_dir, &camera->basis);
	return (normalize(world_dir));
}

void	render_pixel(int x, int y, t_scene *scene, t_img *img)
{
	t_ray	ray;
	t_rgb	colours[64];
	t_rgb	final_colour;
	int		i;

	i = -1;
	ray.origin = scene->camera.pos;
	while (++i < scene->consts.rpp)
	{
		ray.dir = get_ray_dir(&scene->camera, x, y, scene->consts.px_offset[i]);
		ray.intsec = find_intersection(&ray, scene->objs->content);
		if (!ray.intsec.obj) {
			colours[i] = (t_rgb){0, 0, 0};
			continue ;
		}
		cast_shadow_rays(&ray.intsec, scene);
		colours[i] = blinn_phong(scene, &ray.intsec, scale(ray.dir, -1));
	}
	final_colour = rgb_average(colours, scene->consts.rpp);
	put_pixel(&(t_pixel){x, y, final_colour}, img);
}

void	render_scene(t_mlx *mlx)
{
	int		i;
	int		j;

	i = -1;
	while (++i < WIN_HEIGHT - 1)
	{
		j = -1;
		while (++j < WIN_WIDTH - 1)
		{
			render_pixel(j, i, &mlx->scene, &mlx->img);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}
