/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:50:15 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/21 15:26:06 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
/*
void	print_scene(t_scene *scene)
{
	printf("ambient light brightness ratio = %f\n", scene->ambient_light.brightness);
	printf("ambient light rbg = %d,%d,%d\n", scene->ambient_light.colour.r, scene->ambient_light.colour.g, scene->ambient_light.colour.b);

	printf("camera pos = %f,%f,%f\n", scene->camera.pos.x, scene->camera.pos.y, scene->camera.pos.z);
	printf("camera orientation = %f,%f,%f\n", scene->camera.oriention.x, scene->camera.oriention.y, scene->camera.oriention.z);
	printf("camera FOV = %d\n", scene->camera.fov);
	
	printf("light source pos = %f,%f,%f\n", scene->light_src.pos.x, scene->light_src.pos.y, scene->light_src.pos.z);
	printf("light brightness ratio %f\n", scene->light_src.brightness);	
}
*/

void	init_mlx_data(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		exit(EXIT_FAILURE);
	mlx->win = mlx_new_window(mlx->ptr, WIN_LEN, WIN_HEIGHT, "FdF");
	if (!mlx->win)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		exit(EXIT_FAILURE);
	}
}

void	init_img_data(t_img *img, t_mlx *mlx)
{
	img->ptr = mlx_new_image(mlx->ptr, WIN_LEN, WIN_HEIGHT);
	if (!img->ptr)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, \
							&mlx->img.line_len, &mlx->img.endian);
	if (!img->addr)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		mlx_destroy_display(mlx->ptr);
		free(mlx->img.ptr);
		free(mlx->ptr);
		exit(EXIT_FAILURE);
	}
}

void	free_mem(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free_arrlst(mlx->scene.objs, free);
	free(mlx->ptr);
}

int main(int argc, char **argv)
{
	t_mlx	mlx;
	
	if (argc != 2)
		return (1);
	mlx.scene.objs = init_arrlst(4);
	if (!parse(argv[1], &mlx.scene))
		return (1);
	
	init_mlx_data(&mlx);
	init_img_data(&mlx.img, &mlx);
	
	mlx_hook(mlx.win, KEY_PRS_EVT, 1L << 0, key_event, &mlx);
//	mlx_hook(mlx.win, BTN_PRS_EVT, 1L << 2, mouse_event, &mlx);
	mlx_hook(mlx.win, DESTROY_EVT, 1L << 17, close_window, &mlx);
	mlx_loop(mlx.ptr);
}
