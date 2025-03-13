/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:47:17 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 16:59:30 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	get_pl_t(t_ray *ray, t_pl *pl)
{
	double		t;

	t = dot(pl->normal, ray->dir);
	if (fabs(t) < 0.000001) // checks if parallel
		return (-1);
	t = dot(pl->normal, sub(pl->point, ray->origin)) / t;
	return (t);
}

void	get_pl_intsec_data(t_ray *ray, t_pl *pl, t_intsec *intsec)
{
	intsec->t = get_pl_t(ray, pl);
	if (intsec->t >= 0)
	{
		intsec->pos = add(ray->origin, scale(ray->dir, intsec->t));
		intsec->colour = pl->colour;
		intsec->normal = pl->normal;
		intsec->obj = (void *)pl;
		intsec->surf = pl->surf;
	}	
}
