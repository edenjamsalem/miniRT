/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:50:15 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/10 15:24:39 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
/*
void	print_scene(t_scene *scene)
{
	printf("ambient light brightness ratio = %f\n", scene->ambient_light.brightness);
	printf("ambient light rbg = %d,%d,%d\n", scene->ambient_light.colour.r, scene->ambient_light.colour.g, scene->ambient_light.colour.b);

	printf("camera pos = %f,%f,%f\n", scene->camera.pos.x, scene->camera.pos.y, scene->camera.pos.z);
	printf("camera orientation = %f,%f,%f\n", scene->camera.forward.x, scene->camera.forward.y, scene->camera.forward.z);
	printf("camera FOV = %d\n", scene->camera.fov);
	
	printf("light source pos = %f,%f,%f\n", scene->light.pos.x, scene->light.pos.y, scene->light.pos.z);
	printf("light brightness ratio %f\n", scene->light.brightness);	
}
*/

void	free_mem(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free_arrlst(mlx->scene.objs, free);
	free_arrlst(mlx->scene.lights, free);
	free(mlx->ptr);
}

void	init_project(t_mlx *mlx, t_scene *scene)
{
	init_mlx_data(mlx);
	init_img_data(&mlx->img, mlx);
	init_world_basis(&scene->consts.world);
	init_local_basis(&scene->camera.basis, scene->camera.orientation, &scene->consts.world);
	scene->consts.rpp = 2;
	scene->consts.shadow_rpp = 20;
	init_offset(&scene->consts);
}

// 	TODO:
//	- implement multiray casting only for borders
//	- fix rendering inside objects
//	- make light sources visible
//	- try to get threads working for efficiency

int main(int argc, char **argv)
{
	t_mlx	mlx;
	struct timeval	start; // for testing only
	struct timeval	end;
	int		nbr_cores;
	
	(void)argc;
	gettimeofday(&start, NULL);
	nbr_cores = sysconf(_SC_NPROCESSORS_ONLN);
	
	parse(argv[1], &mlx.scene);
	init_project(&mlx, &mlx.scene);
	render_pixels(&mlx);

	gettimeofday(&end, NULL);
	printf("time = %f\n", calc_time_diff(&start, &end) / 1000);
	
	mlx_hook(mlx.win, KEY_PRS_EVT, 1L << 0, key_event, &mlx);
//	mlx_hook(mlx.win, BTN_PRS_EVT, 1L << 2, mouse_event, &mlx);
	mlx_hook(mlx.win, DESTROY_EVT, 1L << 17, close_window, &mlx);
	mlx_loop(mlx.ptr);
}
