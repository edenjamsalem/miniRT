/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:53 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/26 14:12:32 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_mlx_data(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		exit(EXIT_FAILURE);
	mlx->win = mlx_new_window(mlx->ptr, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!mlx->win)
	{
		free_mem(mlx);
		exit(EXIT_FAILURE);
	}
}

void	init_img_data(t_img *img, t_mlx *mlx)
{
	img->ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img->ptr)
	{
		free_mem(mlx);
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, \
							&mlx->img.line_len, &mlx->img.endian);
	if (!img->addr)
	{
		free_mem(mlx);
		exit(EXIT_FAILURE);
	}
}

void	init_scene_basis(t_scene *scene)
{
	scene->world.right.x = 1;
	scene->world.right.y = 0;
	scene->world.right.z = 0;
	
	scene->world.up.x = 0;
	scene->world.up.y = 1;
	scene->world.up.z = 0;
	
	scene->world.forward.x = 0;
	scene->world.forward.y = 0;
	scene->world.forward.z = 1;
}

void	init_camera_basis(t_camera *camera, t_basis *world)
{
	camera->basis.forward = camera->orientation;
	if (check_equal(&world->up, &camera->basis.forward))
		camera->basis.right = normalize(cross(world->forward, camera->basis.forward));
	else
		camera->basis.right = normalize(cross(world->up, camera->basis.forward));

	camera->basis.up = normalize(cross(camera->basis.forward, camera->basis.right));
}