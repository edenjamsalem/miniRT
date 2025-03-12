/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:33:48 by muabdi            #+#    #+#             */
/*   Updated: 2025/03/12 15:34:12 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double    get_h(double t, t_ray *ray, t_cy *cylinder)
{
    t_vec3 p;
    double h;
    
    p = add(ray->origin, scale(ray->direction, t));
    h = dot(sub(p, cylinder->center), cylinder->normal);
    return (h);
}


double  get_t(double t[2], t_ray *ray, t_cy *cylinder)
{
    double h1;
    double h2;

    h1 = get_h(t[0], ray, cylinder);
    h2 = get_h(t[1], ray, cylinder);

    if (t[0] > 0 && h1 >= 0 && h1 <= cylinder->height && t[1] > 0 && h2 >= 0 && h2 <= cylinder->height)
        return fmin(t[0], t[1]);
    else if (t[0] > 0 && h1 >= 0 && h1 <= cylinder->height)
        return t[0];
    else if (t[1] > 0 && h2 >= 0 && h2 <= cylinder->height)
        return t[1];
    else
        return -1.0;

}

double get_cy_t(t_ray *ray, t_cy *cylinder)
{
    t_vec3 oc;
    double a, b, c, discriminant;
    double t[2];

    oc = sub(ray->origin, cylinder->center);
    a = 1 - pow(dot(ray->direction, cylinder->normal), 2);
    b = 2 * (dot(ray->direction, oc) - dot(ray->direction, cylinder->normal) * dot(oc, cylinder->normal));
    c = dot(oc, oc) - pow(dot(oc, cylinder->normal), 2) - pow(cylinder->diameter / 2.0, 2);
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1.0;

    t[0] = (-b - sqrt(discriminant)) / (2 * a);
    t[1] = (-b + sqrt(discriminant)) / (2 * a);

    return (get_t(t, ray, cylinder));
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
