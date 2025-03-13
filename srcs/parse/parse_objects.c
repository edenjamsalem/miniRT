/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:37:05 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 17:55:36 by eamsalem         ###   ########.fr       */
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

void	get_sp_data(t_parse *parse, t_scene *scene)
{
	t_sp	*sp;
	int			no_elems;

	no_elems = ft_2darr_len((void **)parse->data);
	if (no_elems < 4 || no_elems > 5)
		perror_exit(LINE_ARG_COUNT, parse, 0);
	
	sp = malloc(sizeof(t_sp));
	if (!sp)
		perror_exit(MALLOC, parse, 0);
	append_arrlst(scene->objs, sp);
	
	sp->shape = SP;
	if (!assign_vector(&sp->center, parse->data[1]))
		perror_exit(VEC_COUNT, parse, 1);
	sp->diameter = ft_atof(parse->data[2]);
	sp->radius = sp->diameter / 2.0;
	sp->camera_inside = false;
	
	if (!assign_rgb(&sp->colour, parse->data[3]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 3);
	if (no_elems == 5 && !assign_material(&sp->surf, parse->data[4]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 4);
	else if (no_elems == 4)
		assign_default_material(&sp->surf);
}

void	get_pl_data(t_parse *parse, t_scene *scene)
{
	t_pl	*pl;
	int		no_elems;

	no_elems = ft_2darr_len((void **)parse->data);
	if (no_elems < 4 || no_elems > 5)
		perror_exit(LINE_ARG_COUNT, parse, 0);
	pl = malloc(sizeof(t_pl));
	if (!pl)
		perror_exit(MALLOC, parse, 0);
	append_arrlst(scene->objs, pl);
	
	pl->shape = PL;
	if (!assign_vector(&pl->point, parse->data[1]))
		perror_exit(VEC_COUNT, parse, 1);
	if (!assign_vector(&pl->normal, parse->data[2]))
		perror_exit(VEC_COUNT, parse, 2);
	
	if (!vector_in_range(&pl->normal, -1.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, parse, 2);	
	if (!assign_rgb(&pl->colour, parse->data[3]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 3);

	if (no_elems == 5 && !assign_material(&pl->surf, parse->data[4]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 4);
	else if (no_elems == 4)
		assign_default_material(&pl->surf);
}

void	get_cy_data(t_parse *parse, t_scene *scene)
{
	t_cy	*cy;
	int			no_elems;

	no_elems = ft_2darr_len((void **)parse->data);
	if (no_elems < 6 || no_elems > 7)
		perror_exit(LINE_ARG_COUNT, parse, 0);

	cy = malloc(sizeof(t_cy));
	if (!cy)
		perror_exit(MALLOC, parse, 0);
	append_arrlst(scene->objs, cy);
	
	cy->shape = CY;
	if (!assign_vector(&cy->center, parse->data[1]))
		perror_exit(VEC_COUNT, parse, 1);
	if (!assign_vector(&cy->axis, parse->data[2]))
		perror_exit(VEC_COUNT, parse, 2);
	
	cy->diameter = ft_atof(parse->data[3]);
	cy->radius = cy->diameter / 2.0;
	cy->rad_sqr = cy->radius * cy->radius;
	cy->height = ft_atof(parse->data[4]);
	cy->top_h = cy->height / 2;
	cy->bottom_h = -cy->height / 2;
	cy->camera_inside = false;

	if (!vector_in_range(&cy->axis, -1.0, 1.0))
		perror_exit(ARG_OUT_OF_RANGE, parse, 2);
	if (!assign_rgb(&cy->colour, parse->data[5]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 5);
		
	if (no_elems == 7 && !assign_material(&cy->surf, parse->data[6]))
		perror_exit(ARG_OUT_OF_RANGE, parse, 6);
	else if (no_elems == 6)
		assign_default_material(&cy->surf);
}
