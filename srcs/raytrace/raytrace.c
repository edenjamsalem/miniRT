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

t_vec3	get_ray_dir(t_camera *camera, int x, int y)
{
	t_vec3	ndc_dir;
	t_vec3	world_dir;
	double	aspect_ratio;

	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	ndc_dir.x = (((x + 0.5) / (double)WIN_WIDTH * 2) - 1) * aspect_ratio;
	ndc_dir.y = 1 - ((y + 0.5) / (double)WIN_HEIGHT * 2);

	ndc_dir.x *= tan(camera->fov / 2 * PI / 180);
	ndc_dir.y *= tan(camera->fov / 2 * PI / 180);
	ndc_dir.z = -1;

	// print_vector(ndc_dir);

	world_dir = transform_ndc_to_worldspace(&ndc_dir, &camera->basis);

	return (world_dir);
}

void	raytrace(t_scene *scene, t_mlx *mlx)
{
	t_ray		ray;
	t_intsec	intsec;
	int			i;
	int			j;

	i = 0;
	ray.origin = scene->camera.pos;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			ray.direction = get_ray_dir(&scene->camera, i, j);
			intsec = check_plane_intersection(&ray, (t_plane *)scene->objs->content[0]);
			put_pixel(&mlx->img, &(t_vec3){i, j, 0}, &intsec.colour);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	printf("FINISHED RAYTRACE\n");
}
