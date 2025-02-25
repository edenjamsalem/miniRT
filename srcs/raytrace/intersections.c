/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:30:49 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/25 17:38:39 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


t_intsec	check_sphere_intersection(t_ray *ray, t_sphere *sphere)
{
	t_intsec	intersection;

	
	
}

t_intsec	find_intersection(t_ray *ray, void **objs)
{
	int			i;
	t_intsec	current;
	t_intsec	nearest;

	i = 0;
	while (objs[i])
	{
		if (((t_sphere *)objs[i])->shape == SPHERE)
			current = check_sphere_intersection(ray, objs[i]);
		else if (((t_plane *)objs[i])->shape == PLANE)
			current = check_plane_intersection(ray, objs[i]);
		else if (((t_cylinder *)objs[i])->shape == CYLINDER)
			current = check_cylinder_intersection(ray, objs[i]);
		if (is_closer(current, nearest))
			nearest = current;
	}
	return (nearest);
}

