/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:47:17 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 16:59:30 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	get_pl_t(t_ray *ray, t_pl *plane)
{
	double		t;

	t = dot(plane->normal, ray->dir);
	if (fabs(t) < 0.000001) // checks if parallel
		return (-1);
	t = dot(plane->normal, sub(plane->point, ray->origin)) / t;
	return (t);
}

void	get_pl_intsec_data(t_ray *ray, t_pl *plane, t_intsec *intsec)
{
	intsec->t = get_pl_t(ray, plane);
	if (intsec->t >= 0)
	{
		intsec->pos = add(ray->origin, scale(ray->dir, intsec->t));
		intsec->colour = plane->colour;
		intsec->normal = plane->normal;
		intsec->obj = (void *)plane;
		intsec->surf = plane->surf;
	}	
}
