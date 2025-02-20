/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:50:15 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/20 17:51:35 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

int main(int argc, char **argv)
{
	t_scene scene;
	
	if (argc != 2)
		return (1);
	scene.objs = init_arrlst(4);
	if (!parse_file(argv[1], &scene))
		return (1);
	free_arrlst(scene.objs, free);
}