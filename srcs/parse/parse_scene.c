/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:16:36 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/19 17:01:36 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	get_ambient_light_data(t_parse *parse, t_scene *scene)
{
	if (ft_2darr_len((void **)parse->data) != 3)
		perror_exit(LINE_ARG_COUNT, parse, 0);
	scene->ambient_light.brightness = ft_atof(parse->data[1]);
	if (!in_range(scene->ambient_light.brightness, 0.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, parse, 1);
	if (!assign_rgb(&scene->ambient_light.colour, parse->data[2]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 2);
}

void	get_camera_data(t_parse *parse, t_scene *scene)
{
	if (ft_2darr_len((void **)parse->data) != 4)
		perror_exit(LINE_ARG_COUNT, parse, 0);
	if (!assign_vector(&scene->camera.pos, parse->data[1]))
		perror_exit(VEC_COUNT, parse, 1);
	if (!assign_vector(&scene->camera.orientation, parse->data[2]))
		perror_exit(VEC_COUNT, parse, 2);
	if (!vector_in_range(&scene->camera.orientation, -1.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, parse, 2);
	scene->camera.orientation = normalize(scene->camera.orientation);
	scene->camera.fov = ft_atoi(parse->data[3]);
	if (!in_range(scene->camera.fov, 0, 180))
		perror_exit(ARG_OUT_OF_RANGE, parse, 3);
	scene->camera.fov_tan = tan((scene->camera.fov / 2.0) * (PI / 180));
	scene->camera.aspect_r = (double)WIN_WIDTH / (double)WIN_HEIGHT;
}

void	get_light_data(t_parse *parse, t_scene *scene)
{
	t_light		*light;
	int			num_elems;

	num_elems = ft_2darr_len((void **)parse->data);
	if (num_elems < 3 || num_elems > 4)
		perror_exit(LINE_ARG_COUNT, parse, 0);
	light = malloc(sizeof(t_light));
	if (!light)
		perror_exit(MALLOC, parse, 0);
	append_arrlst(scene->lights, light);
	if (!assign_vector(&light->center, parse->data[1]))
		perror_exit(VEC_COUNT, parse, 1);
	light->brightness = ft_atof(parse->data[2]);
	if (!in_range(light->brightness, 0.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, parse, 2);
	light->radius = 10;
	if (num_elems == 4 && !assign_rgb(&light->colour, parse->data[3]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 3);
	else if (num_elems == 3)
		assign_rgb(&light->colour, "255,255,255");
}
