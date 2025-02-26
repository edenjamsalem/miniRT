/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:50:15 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/26 17:50:36 by eamsalem         ###   ########.fr       */
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
	
	printf("light source pos = %f,%f,%f\n", scene->light_src.pos.x, scene->light_src.pos.y, scene->light_src.pos.z);
	printf("light brightness ratio %f\n", scene->light_src.brightness);	
}
*/

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
	parse(argv[1], &mlx.scene);
	init_mlx_data(&mlx);
	init_img_data(&mlx.img, &mlx);
	init_scene_basis(&mlx.scene);
	init_camera_basis(&mlx.scene.camera, &mlx.scene.world);
	raytrace(&mlx.scene, &mlx);
//	phong();
//	generate_img();
	mlx_hook(mlx.win, KEY_PRS_EVT, 1L << 0, key_event, &mlx);
//	mlx_hook(mlx.win, BTN_PRS_EVT, 1L << 2, mouse_event, &mlx);
	mlx_hook(mlx.win, DESTROY_EVT, 1L << 17, close_window, &mlx);
	mlx_loop(mlx.ptr);
}
