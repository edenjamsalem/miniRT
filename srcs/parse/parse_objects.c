/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:37:05 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/12 15:45:17 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	assign_default_material(t_material *properties)
{
	properties->Ka = 0.2;
	properties->Kd = 0.7;
	properties->Ks = 0.3;
	properties->n = 50;
}

void	get_sphere_data(t_parse *parse, t_scene *scene)
{
	t_sp	*sphere;
	int			no_elems;

	no_elems = ft_2darr_len((void **)parse->data);
	if (no_elems < 4 || no_elems > 5)
		perror_exit(LINE_ARG_COUNT, parse, 0);
	
	sphere = malloc(sizeof(t_sp));
	if (!sphere)
		perror_exit(MALLOC, parse, 0);
	append_arrlst(scene->objs, sphere);
	
	sphere->shape = SP;
	if (!assign_vector(&sphere->center, parse->data[1]))
		perror_exit(VEC_COUNT, parse, 1);
	sphere->diameter = ft_atof(parse->data[2]);
	sphere->radius = sphere->diameter / 2.0;
	sphere->camera_inside = false;
	
	if (!assign_rgb(&sphere->colour, parse->data[3]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 3);
	if (no_elems == 5 && !assign_material(&sphere->properties, parse->data[4]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 4);
	else if (no_elems == 4)
		assign_default_material(&sphere->properties);
}

void	get_plane_data(t_parse *parse, t_scene *scene)
{
	t_pl	*plane;
	int		no_elems;

	no_elems = ft_2darr_len((void **)parse->data);
	if (no_elems < 4 || no_elems > 5)
		perror_exit(LINE_ARG_COUNT, parse, 0);
	plane = malloc(sizeof(t_pl));
	if (!plane)
		perror_exit(MALLOC, parse, 0);
	append_arrlst(scene->objs, plane);
	
	plane->shape = PL;
	if (!assign_vector(&plane->point, parse->data[1]))
		perror_exit(VEC_COUNT, parse, 1);
	if (!assign_vector(&plane->normal, parse->data[2]))
		perror_exit(VEC_COUNT, parse, 2);
	
	if (!vector_in_range(&plane->normal, -1.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, parse, 2);	
	if (!assign_rgb(&plane->colour, parse->data[3]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 3);

	if (no_elems == 5 && !assign_material(&plane->properties, parse->data[4]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 4);
	else if (no_elems == 4)
		assign_default_material(&plane->properties);
}

void	get_cylinder_data(t_parse *parse, t_scene *scene)
{
	t_cy	*cylinder;
	int			no_elems;

	no_elems = ft_2darr_len((void **)parse->data);
	if (no_elems < 6 || no_elems > 7)
		perror_exit(LINE_ARG_COUNT, parse, 0);

	cylinder = malloc(sizeof(t_cy));
	if (!cylinder)
		perror_exit(MALLOC, parse, 0);
	append_arrlst(scene->objs, cylinder);
	
	cylinder->shape = CY;
	if (!assign_vector(&cylinder->center, parse->data[1]))
		perror_exit(VEC_COUNT, parse, 1);
	if (!assign_vector(&cylinder->normal, parse->data[2]))
		perror_exit(VEC_COUNT, parse, 2);
	
	cylinder->diameter = ft_atof(parse->data[3]);
	cylinder->radius = cylinder->diameter / 2.0;
	cylinder->height = ft_atof(parse->data[4]);
	cylinder->camera_inside = false;

	if (!vector_in_range(&cylinder->normal, -1.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, parse, 2);
	if (!assign_rgb(&cylinder->colour, parse->data[5]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 5);
		
	if (no_elems == 7 && !assign_material(&cylinder->properties, parse->data[6]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 6);
	else if (no_elems == 6)
		assign_default_material(&cylinder->properties);
}
