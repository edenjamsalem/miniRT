/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:36:59 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 17:01:32 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static double get_t(double t[2])
{
	if (t[0] > 0 && t[1] > 0)
		return (fmin(t[0], t[1]));
	else if (t[0] > 0)
		return (t[0]);
	else if (t[1] > 0)
		return (t[1]);
	else	
		return (-1);
}

double	get_sp_t(t_ray *ray, t_sp *sp)
{
    t_quadratic q;
	double		t[2];
	t_vec3		l;

	l = sub(ray->origin, sp->center);
	q.b = 2.0 * dot(ray->dir, l);
	q.c = dot(l, l) - (sp->radius * sp->radius);

	q.discriminant = (q.b * q.b) - (4.0 * q.c);
	if (q.discriminant < 0)
		return (-1);
	if (q.discriminant == 0)
		return (-q.b / 2);
	
	q.discriminant = sqrt(q.discriminant);
	t[0] = (-q.b + q.discriminant) / 2;
	t[1] = (-q.b - q.discriminant) / 2;
	return (get_t(t));
}

void	get_sp_intsec_data(t_ray *ray, t_sp *sp, t_intsec *intsec)
{
	intsec->t = get_sp_t(ray, sp);
	if (intsec->t >= 0)
	{
		intsec->pos = add(ray->origin, scale(ray->dir, intsec->t));
		intsec->colour = sp->colour;
		intsec->normal = normalize(sub(intsec->pos, sp->center));
		if (sp->camera_inside)
			intsec->normal = scale(intsec->normal, -1);
		intsec->obj = (void *)sp;
		intsec->surf = sp->surf;
	}
}

bool	camera_in_sp(t_sp *sp, t_camera *camera)
{
	t_vec3 len;

	len = sub(camera->pos, sp->center);
	return (dot(len, len) < (sp->radius * sp->radius));
}
