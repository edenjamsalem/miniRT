/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:33:48 by muabdi            #+#    #+#             */
/*   Updated: 2025/03/10 17:59:14 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double get_cy_t(t_ray *ray, t_cy *cylinder)
{
    t_vec3 oc;
    double a, b, c, discriminant;
    double t1, t2;
    t_vec3 p1, p2;
    double h1, h2;

    oc = sub(ray->origin, cylinder->center);
    a = dot(ray->direction, ray->direction) - pow(dot(ray->direction, cylinder->normal), 2);
    b = 2 * (dot(ray->direction, oc) - dot(ray->direction, cylinder->normal) * dot(oc, cylinder->normal));
    c = dot(oc, oc) - pow(dot(oc, cylinder->normal), 2) - pow(cylinder->diameter / 2.0, 2);
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1.0;

    t1 = (-b - sqrt(discriminant)) / (2 * a);
    t2 = (-b + sqrt(discriminant)) / (2 * a);
    p1 = add(ray->origin, scale(ray->direction, t1));
    p2 = add(ray->origin, scale(ray->direction, t2));
    h1 = dot(sub(p1, cylinder->center), cylinder->normal);
    h2 = dot(sub(p2, cylinder->center), cylinder->normal);

    if (t1 > 0 && h1 >= 0 && h1 <= cylinder->height && t2 > 0 && h2 >= 0 && h2 <= cylinder->height)
        return fmin(t1, t2);
    else if (t1 > 0 && h1 >= 0 && h1 <= cylinder->height)
        return t1;
    else if (t2 > 0 && h2 >= 0 && h2 <= cylinder->height)
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
