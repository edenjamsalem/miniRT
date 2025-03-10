/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:47:43 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/10 17:12:01 by eamsalem         ###   ########.fr       */
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

void	get_sphere_data(t_scene *scene, char **data, int line_nbr)
{
	t_sp	*sphere;
	int			no_elems;

	no_elems = ft_2darr_len((void **)data);
	if (no_elems < 4 || no_elems > 5)
		perror_exit(LINE_ARG_COUNT, line_nbr, data, 0, scene);
	
	sphere = malloc(sizeof(t_sp));
	if (!sphere)
		perror_exit(MALLOC, 0, data, 0, scene);
	append_arrlst(scene->objs, sphere);
	
	sphere->shape = SP;
	assign_vector(&sphere->center, data[1]);
	sphere->diameter = ft_atof(data[2]);
	sphere->radius = sphere->diameter / 2.0;
	sphere->camera_inside = false;
	
	if (!assign_rgb(&sphere->colour, data[3]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 3, scene);
	if (no_elems == 5 && !assign_material(&sphere->properties, data[4]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 4, scene);
	else if (no_elems == 4)
		assign_default_material(&sphere->properties);
}

void	get_plane_data(t_scene *scene, char **data, int line_nbr)
{
	t_pl	*plane;
	int		no_elems;

	no_elems = ft_2darr_len((void **)data);
	if (no_elems < 4 || no_elems > 5)
		perror_exit(LINE_ARG_COUNT, line_nbr, data, 0, scene);
	plane = malloc(sizeof(t_pl));
	if (!plane)
		perror_exit(MALLOC, 0, data, 0, scene);
	append_arrlst(scene->objs, plane);
	
	plane->shape = PL;
	assign_vector(&plane->point, data[1]);
	assign_vector(&plane->normal, data[2]);
	
	if (!vector_in_range(&plane->normal, -1.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 2, scene);	
	if (!assign_rgb(&plane->colour, data[3]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 3, scene);

	if (no_elems == 5 && !assign_material(&plane->properties, data[4]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 4, scene);
	else if (no_elems == 4)
		assign_default_material(&plane->properties);
}

void	get_cylinder_data(t_scene *scene, char **data, int line_nbr)
{
	t_cy	*cylinder;
	int			no_elems;

	no_elems = ft_2darr_len((void **)data);
	if (no_elems < 6 || no_elems > 7)
		perror_exit(LINE_ARG_COUNT, line_nbr, data, 0, scene);

	cylinder = malloc(sizeof(t_cy));
	if (!cylinder)
		perror_exit(MALLOC, 0, data, 0, scene);
	append_arrlst(scene->objs, cylinder);
	
    cylinder->shape = CY;
	assign_vector(&cylinder->center, data[1]);
	assign_vector(&cylinder->normal, data[2]);
	cylinder->diameter = ft_atof(data[3]);
	cylinder->height = ft_atof(data[4]);
	cylinder->camera_inside = false;

	if (!vector_in_range(&cylinder->normal, -1.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 2, scene);
	if (!assign_rgb(&cylinder->colour, data[5]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 5, scene);
		
	if (no_elems == 7 && !assign_material(&cylinder->properties, data[6]))
		perror_exit(ARG_OUT_OF_RANGE, line_nbr, data, 6, scene);
	else if (no_elems == 6)
		assign_default_material(&cylinder->properties);
}
