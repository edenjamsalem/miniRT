/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:40:51 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/07 12:40:26 by eamsalem         ###   ########.fr       */
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

void	get_light_data(t_scene *scene, char **data, int line_nbr)
{
	t_light		*light;
	int			no_elems;

	no_elems = ft_2darr_len((void **)data);
	if (no_elems < 3 || no_elems > 4)
		perror_exit(LINE_ARG_COUNT, line_nbr, data, 0, scene);

	light = malloc(sizeof(t_light));
	if (!light)
		perror_exit(MALLOC, line_nbr, data, 0, scene);
		
	append_arrlst(scene->lights, light);	
	assign_vector(&light->center, data[1]);
	light->brightness = ft_atof(data[2]);
	light->dir = (t_vec3){0, 0, 0};
	light->visibility = 0.0;
	light->radius = 10; // make dynamic later
	
	if (!in_range(light->brightness, 0.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 2, scene);	
	if (no_elems == 4 && !assign_rgb(&light->colour, data[3]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 3, scene);
	else if (no_elems == 3)
		assign_rgb(&light->colour, "255,255,255");
}	
