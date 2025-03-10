/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:30:49 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/06 14:59:03 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
		if (((t_sphere *)objs[i])->shape == SPHERE)
			get_sp_intsec_data(ray, objs[i], &current);
		else if (((t_plane *)objs[i])->shape == PLANE)
			get_pl_intsec_data(ray, objs[i], &current);
		else if (((t_cylinder *)objs[i])->shape == CYLINDER)
			get_cy_intsec_data(ray, objs[i], &current);
		if (current.t >= 0 && current.t < nearest.t)
			nearest = current;
		i++;
	}
	return (nearest);
}
