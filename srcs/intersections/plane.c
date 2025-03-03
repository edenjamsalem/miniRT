/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:47:17 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/03 18:12:03 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	get_pl_t(t_ray *ray, t_plane *plane)
{
	double		t;

	t = dot(plane->normal, ray->direction);
	if (fabs(t) < 0.000001) // checks if parallel
		return (-1);
	t = dot(plane->normal, sub(plane->point, ray->origin)) / t;
	return (t);
}

void	get_pl_intsec_data(t_ray *ray, t_plane *plane, t_intsec *intsec)
{
	intsec->t = get_pl_t(ray, plane);
	if (intsec->t >= 0)
	{
		intsec->pos = add(ray->origin, scale(ray->direction, intsec->t));
		intsec->shape = PLANE;
		intsec->colour = plane->colour;
		intsec->normal = plane->normal;
		intsec->obj = (void *)plane;
	}	
}
