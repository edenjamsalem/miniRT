/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:33:48 by muabdi            #+#    #+#             */
/*   Updated: 2025/03/10 17:50:21 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double get_cy_t(t_ray *ray, t_cy *cylinder)
{
    t_vec3 oc = sub(ray->origin, cylinder->center);
    double a = dot(ray->direction, ray->direction) - pow(dot(ray->direction, cylinder->normal), 2);
    double b = 2 * (dot(ray->direction, oc) - dot(ray->direction, cylinder->normal) * dot(oc, cylinder->normal));
    double c = dot(oc, oc) - pow(dot(oc, cylinder->normal), 2) - pow(cylinder->diameter / 2.0, 2);
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1.0;

    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t1 > 0 && t2 > 0)
        return fmin(t1, t2);
    else if (t1 > 0)
        return t1;
    else if (t2 > 0)
        return t2;
    else
        return -1.0;
}

void get_cy_intsec_data(t_ray *ray, t_cy *cylinder, t_intsec *intsec)
{
    intsec->t = get_cy_t(ray, cylinder);
    if (intsec->t >= 0)
    {
        intsec->pos = add(ray->origin, scale(ray->direction, intsec->t));
        intsec->colour = cylinder->colour;
        intsec->normal = normalize(sub(intsec->pos, cylinder->center));
        intsec->obj = (void *)cylinder;
        intsec->properties = cylinder->properties;
    }
}