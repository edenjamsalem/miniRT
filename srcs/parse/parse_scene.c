/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:40:51 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/04 15:47:22 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	get_ambient_light_data(t_scene *scene, char **data, int line_nbr)
{
	if (ft_2darr_len((void **)data) != 3)
		perror_exit(LINE_ARG_COUNT, line_nbr, data, 0, scene);
		
	scene->ambient_light.brightness = ft_atof(data[1]);
	
	if (!in_range(scene->ambient_light.brightness, 0.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 1, scene);
	if (!assign_rgb(&scene->ambient_light.colour, data[2]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 2, scene);
}

void	get_camera_data(t_scene *scene, char **data, int line_nbr)
{
	if (ft_2darr_len((void **)data) != 4)
		perror_exit(LINE_ARG_COUNT, line_nbr, data, 0, scene);

	assign_vector(&scene->camera.pos, data[1]);
	assign_vector(&scene->camera.orientation, data[2]);
	scene->camera.fov = ft_atoi(data[3]);
	scene->camera.fov_tan = tan((scene->camera.fov / 2.0) * (PI / 180));
	scene->camera.aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	
	if (!vector_in_range(&scene->camera.orientation, -1.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 2, scene);
	if (!in_range(scene->camera.fov, 0, 180))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 3, scene);
}

void	get_light_src_data(t_scene *scene, char **data, int line_nbr)
{
	int	no_elems;

	no_elems = ft_2darr_len((void **)data);
	if (no_elems < 3 || no_elems > 4)
		perror_exit(LINE_ARG_COUNT, line_nbr, data, 0, scene);
	
	assign_vector(&scene->light.pos, data[1]);
	scene->light.brightness = ft_atof(data[2]);
	scene->light.dir = (t_vec3){0, 0, 0};
	if (!in_range(scene->light.brightness, 0.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 2, scene);
		
	if (no_elems == 4 && !assign_rgb(&scene->light.colour, data[3]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 3, scene);
	else if (no_elems == 3)
		assign_rgb(&scene->light.colour, "255,255,255");
}	
