/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:15:45 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 13:14:22 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	camera_in_sp(t_sp *sp, t_camera *camera)
{
	t_vec3	len;

	len = sub(camera->pos, sp->center);
	return (dot(len, len) < (sp->radius * sp->radius));
}

bool	camera_in_cy(t_cy *cy, t_camera *camera)
{
	t_vec3	to_camera;
	double	axis_project;
	t_vec3	radial_vec;

	to_camera = sub(camera->pos, cy->center);
	axis_project = dot(to_camera, cy->axis);
	if (axis_project < (cy->bottom_h) || axis_project > (cy->top_h))
		return (false);
	radial_vec = sub(to_camera, scale(cy->axis, axis_project));
	return (dot(radial_vec, radial_vec) < cy->rad_sqr);
}

void	check_camera_inside_objs(void **objs, t_camera *camera)
{
	int			i;

	i = 0;
	while (objs[i])
	{
		if (((t_sp *)objs[i])->shape == SP)
		{
			if (camera_in_sp((t_sp *)objs[i], camera))
				((t_sp *)objs[i])->camera_inside = true;
		}
		else if (((t_cy *)objs[i])->shape == CY)
		{
			if (camera_in_cy((t_cy *)objs[i], camera))
				((t_cy *)objs[i])->camera_inside = true;
		}
		i++;
	}
}

t_intsec	find_intersection(t_ray *ray, void **objs)
{
	int			i;
	t_intsec	current;
	t_intsec	nearest;

	init_intsec(&nearest);
	i = 0;
	while (objs[i])
	{
		init_intsec(&current);
		if (((t_sp *)objs[i])->shape == SP)
			get_sp_intsec_data(ray, objs[i], &current);
		else if (((t_pl *)objs[i])->shape == PL)
			get_pl_intsec_data(ray, objs[i], &current);
		else if (((t_cy *)objs[i])->shape == CY)
			get_cy_intsec_data(ray, objs[i], &current);
		if (current.t >= 0 && current.t < nearest.t)
			nearest = current;
		i++;
	}
	return (nearest);
}
